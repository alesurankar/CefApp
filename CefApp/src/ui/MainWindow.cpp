#include "MainWindow.h"
#include "../cef/MyCefClient.h"

using namespace std::string_literals;

static constexpr const char* wndClassName = "CefApp.MainWindow.Win32";

namespace
{
	LRESULT CALLBACK HandleWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
			case WM_LBUTTONDOWN:
			{
				ReleaseCapture();
				PostMessage(GetParent(hwnd), WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);

				return 0;
			}
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	LRESULT CALLBACK MainWindowWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		MainWindow* window = nullptr;

		if (msg != WM_NCCREATE)
			window = MainWindow::GetWindow(hWnd);

		switch (msg) {
			case WM_NCCREATE:
			{
				CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
				window = static_cast<MainWindow*>(cs->lpCreateParams);

				window->AttachHWND(hWnd);
				SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);

				return TRUE;
			}
			break;

			case WM_CREATE:
			{
				if (window) {
					window->CreateBrowser();
					PostMessage(hWnd, WM_SIZE, 0, 0);
				}
				return 0;
			}
			break;

			case WM_ERASEBKGND:
			{
				if (window && window->HasBrowserWindow())
					return 1;
			}
			break;

			case WM_SIZE:
			{
				if (!window) break;

				if (wParam == SIZE_MINIMIZED) {
					window->isMinimized_ = true;
					window->isMaximized_ = false;
					SetLayeredWindowAttributes(hWnd, 0, 0, LWA_ALPHA);
				}
				if (wParam == SIZE_MAXIMIZED) {
					window->isMaximized_ = true;
					window->isMinimized_ = false;
					SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
				}
				if (wParam == SIZE_RESTORED) {
					window->isMinimized_ = false;
					window->isMaximized_ = false;
					SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
				}

				window->OnSize(wParam);
			}
			break;

			case WM_GETMINMAXINFO:
			{
				MINMAXINFO* mmi = reinterpret_cast<MINMAXINFO*>(lParam);
				// Set minimum width and height
				mmi->ptMinTrackSize.x = 520;
				mmi->ptMinTrackSize.y = 360;

				// Maximum size = working area
				HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
				MONITORINFO mi{};
				mi.cbSize = sizeof(mi);
				if (GetMonitorInfo(hMonitor, &mi))
				{
					const int border = 4;

					mmi->ptMaxPosition.x = mi.rcWork.left - border;
					mmi->ptMaxPosition.y = mi.rcWork.top - border;

					mmi->ptMaxTrackSize.x = (mi.rcWork.right - mi.rcWork.left) + border * 2;
					mmi->ptMaxTrackSize.y = (mi.rcWork.bottom - mi.rcWork.top) + border * 2;
				}

				return 0;
			}
			break;

			case WM_TIMER:
			{
				if (wParam == MainWindow::TIMER_FADE) {
					if (!window) break;

					if (window->fadeStep <= 0) {
						KillTimer(hWnd, MainWindow::TIMER_FADE);

						switch (window->fadeAction_) {
						case MainWindow::FadeAction::Close:
							PostMessage(hWnd, WM_CLOSE, 0, 0);
							break;
						case MainWindow::FadeAction::Minimize:
							ShowWindow(hWnd, SW_MINIMIZE);
							break;
						case MainWindow::FadeAction::Maximize:
							ShowWindow(hWnd, SW_MAXIMIZE);
							break;
						case MainWindow::FadeAction::Restore:
							ShowWindow(hWnd, SW_RESTORE);
							break;
						default:
							break;
						}

						window->fadeAction_ = MainWindow::FadeAction::None;
					}
					else {
						BYTE alpha = (BYTE)(255 * window->fadeStep / MainWindow::FADE_STEPS);

						switch (window->fadeAction_) {
						case MainWindow::FadeAction::Close:
						case MainWindow::FadeAction::Minimize:
							SetLayeredWindowAttributes(hWnd, 0, alpha, LWA_ALPHA);
							window->fadeStep--;
							break;
						default:
							window->fadeStep = 0;
							break;
						}
					}
				}
			}
			break;

			case WM_NCCALCSIZE:
			{
				if (wParam)
				{
					NCCALCSIZE_PARAMS* p = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);
					if (IsZoomed(hWnd))
					{
						// Get working area of the monitor
						HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
						MONITORINFO mi{};
						mi.cbSize = sizeof(mi);
						if (GetMonitorInfo(hMonitor, &mi))
						{
							RECT& r = p->rgrc[0];
							r.left = mi.rcWork.left;
							r.top = mi.rcWork.top;
							r.right = mi.rcWork.right;
							r.bottom = mi.rcWork.bottom;
						}
					}
					else
					{
						// shrink client rect by border thickness for resizing
						const int border = 8;
						p->rgrc[0].left += border;
						p->rgrc[0].top += 1;    // little hack to remove white artefact on top
						p->rgrc[0].right -= border;
						p->rgrc[0].bottom -= border;
					}
					return 0; // handled
				}
				else
				{
					RECT* pRect = reinterpret_cast<RECT*>(lParam);
					return 0;
				}
			}
			break;

			case WM_CLOSE:
			{
				if (window) {
					OutputDebugStringA("WM_CLOSE triggered\n");
					window->RequestClose();
					return 0;
				}
				DestroyWindow(hWnd);
				return 0;
			}
			break;

			case WM_APP + 99:
			{
				DestroyWindow(hWnd);
				return 0;
			}
			break;

			case WM_DESTROY:
			{
				// Clear the window pointer from GWLP_USERDATA
				SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
				PostQuitMessage(0);
				return 0;
			}
			break;
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

	auto* window = new MainWindow();
	HWND hWnd = CreateWindowExA(
		0,
		wndClassName,
		"CEF",
		//WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		WS_POPUP | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CLIPCHILDREN,
		200, 50, 1400, 900,
		nullptr,
		nullptr,
		hInstance,
		window
	);

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

bool MainWindow::HasBrowserWindow() const
{
	// Return true only if client exists and its browser window is valid
	if (!client_)
		return false;

	if (auto browser = client_->GetBrowser())  // safe null check
		if (auto host = browser->GetHost())   // safe host check
			return host->GetWindowHandle() != nullptr;

	return false;
}

void MainWindow::OnSize(WPARAM wParam)
{
	if (wParam == SIZE_MINIMIZED) return;

	RECT rect{};
	GetClientRect(hWnd_, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	if (hHandle_)
	{
		SetWindowPos(hHandle_, nullptr,
			80, 1, width - 260, 37,
			SWP_NOZORDER | SWP_NOACTIVATE);
	}

	if (hWndBrowser_)
	{
		SetWindowPos(hWndBrowser_, nullptr, 0, 0,
			width, height,
			SWP_NOZORDER | SWP_NOACTIVATE);
	}

	if (overlay_)
		overlay_->OnSize(width, height);
	RaiseHandle();
}

void MainWindow::SetBrowserHWND(HWND hWndBrowser)
{
	hWndBrowser_ = hWndBrowser;

	// create handle AFTER browser exists
	hHandle_ = CreateWindowExA(
		//0,                           // change to this to show the hendleBar
		WS_EX_TRANSPARENT,			   // change to this to hide the handleBar
		"STATIC",
		nullptr,
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0,
		hWnd_,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	); 
	SetWindowLongPtr(hHandle_, GWLP_WNDPROC, (LONG_PTR)HandleWndProc);
	RaiseHandle();
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

void MainWindow::StartFade(FadeAction action)
{
	LONG ex = GetWindowLong(hWnd_, GWL_EXSTYLE);
	SetWindowLong(hWnd_, GWL_EXSTYLE, ex | WS_EX_LAYERED);

	fadeStep = FADE_STEPS;
	fadeAction_ = action;

	SetTimer(hWnd_, TIMER_FADE, 10, NULL);
}

void MainWindow::CreateOverlayWindow()
{
	overlay_ = std::make_unique<OverlayWindow>();
	overlay_->CreateOverlayWindow(hWnd_); 
	RaiseOverlayWindow();
}
