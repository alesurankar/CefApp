#include "MainWindow.h"
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
//#include <commctrl.h>
//#pragma comment(lib, "Comctl32.lib")
#include "../platform/MyWinX.h" 
#include "../cef/MyCefClient.h"

using namespace std::string_literals;

static constexpr const char* wndClassName = "CefApp.MainWindow.Win32";

namespace 
{
	LRESULT CALLBACK MainWindowWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg) {
			case WM_NCCREATE:
			{
				CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
				auto* window = static_cast<MainWindow*>(cs->lpCreateParams);

				window->AttachHWND(hWnd);
				SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);

				return TRUE;
			}
			case WM_CREATE:
			{
				MainWindow* window = MainWindow::GetWindow(hWnd);
				if (window) {
					window->CreateBrowser();
					PostMessage(hWnd, WM_SIZE, 0, 0);
				}
				return 0;
			}
			case WM_ERASEBKGND:
			{
				MainWindow* window = MainWindow::GetWindow(hWnd);
				if (window && window->HasBrowserWindow())
					return 1;
				break;
			}
			case WM_SIZE:
				if (MainWindow* window = MainWindow::GetWindow(hWnd))
					window->OnSize(wParam);
				break;
			case WM_NCCALCSIZE:
			{
				if (wParam)
				{
					// lParam is a pointer to NCCALCSIZE_PARAMS
					NCCALCSIZE_PARAMS* pParams = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);

					// Keep the client rect same as original
					pParams->rgrc[0] = pParams->rgrc[0]; // no-op, just for clarity
					return 0; // tells Windows: we handled it
				}
				else
				{
					// lParam is a RECT*
					RECT* pRect = reinterpret_cast<RECT*>(lParam);
					// optionally adjust the rect if needed
					return 0;
				}
			}
			case WM_NCHITTEST:
			{
				LRESULT hit = DefWindowProc(hWnd, msg, wParam, lParam);
			
				if (hit == HTCLIENT)
				{
					POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
					ScreenToClient(hWnd, &pt);
			
					RECT rc;
					GetClientRect(hWnd, &rc);
					const int border = 8; // resize border thickness
			
					// Top edge
					if (pt.y < border)
					{
						if (pt.x < border) return HTTOPLEFT;
						if (pt.x > rc.right - border) return HTTOPRIGHT;
						return HTTOP;
					}
					// Bottom edge
					if (pt.y > rc.bottom - border)
					{
						if (pt.x < border) return HTBOTTOMLEFT;
						if (pt.x > rc.right - border) return HTBOTTOMRIGHT;
						return HTBOTTOM;
					}
					// Left edge
					if (pt.x < border) return HTLEFT;
					// Right edge
					if (pt.x > rc.right - border) return HTRIGHT;
			
					// Everything else draggable
					return HTCAPTION;
				}
				return hit;
			}
			case WM_CLOSE:
			{
				MainWindow* window = MainWindow::GetWindow(hWnd);
				if (window) {
					OutputDebugStringA("WM_CLOSE triggered\n");
					window->RequestClose();
					return 0;
				}
				DestroyWindow(hWnd);
				return 0;
			}
			case WM_APP + 99:
				DestroyWindow(hWnd);
				return 0;
			case WM_DESTROY:
			{
				MainWindow* window = MainWindow::GetWindow(hWnd);
				SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
				delete window;
				PostQuitMessage(0);
				return 0;
			}
		}
		return DefWindowProcA(hWnd, msg, wParam, lParam);
	}
}

HWND CreateMainWindow(HINSTANCE hInstance)
{
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

	auto* window = new MainWindow(nullptr);
	HWND hWnd = CreateWindowExA(
		0,
		wndClassName,
		"CEF",
		//WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		WS_POPUP | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CLIPCHILDREN,
		//WS_POPUP | WS_THICKFRAME | WS_CLIPCHILDREN,
		200, 20, 1360, 1020,
		nullptr,
		nullptr,
		hInstance,
		window
	);
	//SetWindowLong(hWnd, GWL_EXSTYLE,
	//	GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	//SetLayeredWindowAttributes(hWnd, 0, 100, LWA_ALPHA);

	MARGINS margins = { -1 };
	//MARGINS margins = { 1, 1, 1, 1 };
	DwmExtendFrameIntoClientArea(hWnd, &margins);

	if (!hWnd) {
		MessageBoxA(nullptr, "CreateWindowExA failed!", "Error", MB_ICONERROR);
		delete window;
		return nullptr;
	}
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);                  

	return hWnd;
}

void CleanupMainWindow(HINSTANCE hInstance)
{
	UnregisterClassA(wndClassName, hInstance);
}


MainWindow::MainWindow(HWND hWnd)
	:
	hWnd_(hWnd)
{}

void MainWindow::AttachHWND(HWND hWnd)
{
	hWnd_ = hWnd;
}

void MainWindow::CreateBrowser()
{
	client_ = new MyCefClient(hWnd_);
	RECT rect{};
	GetClientRect(hWnd_, &rect);
	CefWindowInfo info;
	info.SetAsChild(hWnd_, CefRect(0, 0, 
		rect.right - rect.left, rect.bottom - rect.top));

	CefBrowserHost::CreateBrowser(
		info,
		client_,
		url_,
		CefBrowserSettings{},
		nullptr,
		nullptr
	);
}

MainWindow* MainWindow::GetWindow(HWND hWnd)
{
	return
		reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
}

void MainWindow::OnSize(WPARAM wParam)
{
	if (wParam == SIZE_MINIMIZED) return;
	if (!hWndBrowser_) return;

	RECT rect{};
	GetClientRect(hWnd_, &rect);
	int left = 20;
	int top = 2;
	SetWindowPos(hWndBrowser_, nullptr, left, top,
		rect.right - left - 2, rect.bottom - top - 2,
		SWP_NOZORDER | SWP_NOACTIVATE);
	//SetWindowPos(hWndBrowser_, nullptr, 0, 0,
	//	rect.right - rect.left, rect.bottom - rect.top,
	//	SWP_NOZORDER | SWP_NOACTIVATE);
}

bool MainWindow::HasBrowserWindow() const
{
	if (!client_) return false;
	auto browser = client_->GetBrowser();
	if (!browser) return false;
	return browser->GetHost()->GetWindowHandle() != nullptr;
}

void MainWindow::SetBrowserHWND(HWND hWndBrowser)
{
	hWndBrowser_ = hWndBrowser; 
	// Make the browser window transparent to mouse hit-testing
	LONG exStyle = GetWindowLong(hWndBrowser_, GWL_EXSTYLE);
	SetWindowLong(hWndBrowser_, GWL_EXSTYLE, exStyle | WS_EX_TRANSPARENT);

	// Force Windows to re-evaluate styles
	SetWindowPos(hWndBrowser_, nullptr, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

void MainWindow::RequestClose()
{
	if (isClosing_ || !client_) {
		DestroyWindow(hWnd_);
		return;
	}

	isClosing_ = true;
	if (auto browser = client_->GetBrowser()) {
		browser->GetHost()->CloseBrowser(true);
	}
}