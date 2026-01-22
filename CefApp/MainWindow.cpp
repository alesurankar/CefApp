#include "MainWindow.h"
#include "NanoCefClient.h"

using namespace std::string_literals;

static constexpr const char* wndClassName = "$client - window$";
static CefRefPtr<NanoCefClient> pClient;
static bool g_isClosing = false;

namespace 
{
	LRESULT CALLBACK MainWindowWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			// Step 5: WM_CREATE fires in window procedure
		case WM_CREATE:
		{
			pClient = new NanoCefClient{ hWnd };
			RECT rect{};
			GetClientRect(hWnd, &rect);
			CefWindowInfo info;
			info.SetAsChild(
				hWnd,
				CefRect(0, 0,
					rect.right - rect.left,
					rect.bottom - rect.top)
			);
			// Step 6: CEF starts renderer process (non-blocking)
			CefBrowserHost::CreateBrowser(
				info,
				pClient,
				"http://localhost:5173/"s,
				CefBrowserSettings{},
				nullptr,
				nullptr
			);
			// Post WM_SIZE to resize browser after creation is complete
			PostMessage(hWnd, WM_SIZE, 0, 0);
			return 0; // back to main message loop
		}
		case WM_SIZE:
			if (wParam != SIZE_MINIMIZED && pClient)
			{
				if (auto pBrowser = pClient->GetBrowser())
				{
					if (auto hWndBrowser = pBrowser->GetHost()->GetWindowHandle())
					{
						RECT rect{};
						GetClientRect(hWnd, &rect);
						SetWindowPos(hWndBrowser, NULL, rect.left, rect.top,
							rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
					}
				}
			}
			break;
		case WM_ERASEBKGND:
			if (pClient)
			{
				if (auto pBrowser = pClient->GetBrowser())
				{
					if (pBrowser->GetHost()->GetWindowHandle())
					{
						return 1;
					}
				}
			}
			break;
		case WM_CLOSE:
			if (!g_isClosing && pClient && pClient->GetBrowser())
			{
				g_isClosing = true;
				pClient->GetBrowser()->GetHost()->CloseBrowser(true);
				return 0;
			}
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		return DefWindowProcA(hWnd, msg, wParam, lParam);
	}
}

// Step 4: Create Win32 window + browser
HWND CreateMainWindow(HINSTANCE hInstance)
{
	HWND hWndBrowser = nullptr;
	WNDCLASSEXA wcex{};
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MainWindowWndProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszClassName = wndClassName;
	if (!RegisterClassExA(&wcex)) {
		MessageBoxA(nullptr, "RegisterClassExA failed!", "Error", MB_ICONERROR);
		return nullptr;
	}

	hWndBrowser = CreateWindowExA(
		0, wndClassName, "CEF",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 
		200, 20, 1360, 1020, 
		nullptr, nullptr, hInstance, nullptr
	);
	if (!hWndBrowser)
	{
		MessageBoxA(nullptr, "CreateWindowExA failed!", "Error", MB_ICONERROR);
		return nullptr;
	}

	ShowWindow(hWndBrowser, SW_SHOWDEFAULT);    // this + 
	UpdateWindow(hWndBrowser);                  // this -> triggers WM_CREATE

	return hWndBrowser;
}

void CleanupMainWindow(HINSTANCE hInstance)
{
	pClient.reset();
	UnregisterClassA(wndClassName, hInstance);
}