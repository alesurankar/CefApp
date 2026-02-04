#include "Window.h"
#include "Client.h"

static constexpr const char* wndClassName = "$client - window$";
static CefRefPtr<Client> pClient;

namespace
{
	LRESULT CALLBACK MainWindowWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg) {
			case WM_CREATE:
			{
				pClient = new Client{ hWnd };
				RECT rect{};
				GetClientRect(hWnd, &rect);
				CefWindowInfo info;
				info.SetAsChild(hWnd, CefRect(0, 0, rect.right - rect.left, rect.bottom - rect.top));

				CefBrowserHost::CreateBrowser(
					info,
					pClient,
					"http://localhost:5173/",
					CefBrowserSettings{},
					nullptr,
					nullptr
				);

				return 0;
			}
			case WM_APP + 1:
				HWND hWndBrowser = reinterpret_cast<HWND>(wParam);
				RECT rect{};
				GetClientRect(hWnd, &rect);
				SetWindowPos(hWndBrowser, NULL, 0, 0,
					rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
		}
	}
}


HWND CreateMainWindow(HINSTANCE hInstance)
{
	HWND hWndMain = nullptr;
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

	hWndMain = CreateWindowExA(
		0, wndClassName, "CEF",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 
		200, 20, 1360, 1020, 
		nullptr, nullptr, hInstance, nullptr
	);
	if (!hWndMain) {
		MessageBoxA(nullptr, "CreateWindowExA failed!", "Error", MB_ICONERROR);
		return nullptr;
	}

	ShowWindow(hWndMain, SW_SHOWDEFAULT);
	UpdateWindow(hWndMain);                  // triggers WM_CREATE

	return hWndMain;
}

void CleanupMainWindow(HINSTANCE hInstance)
{
}