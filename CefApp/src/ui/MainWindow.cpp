#include "MainWindow.h"
#include <util/AppException.h>


using namespace std::string_literals;

// Wnd Procedure stuff
namespace
{
	LRESULT CALLBACK HandleWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_LBUTTONDOWN:
		{
			ReleaseCapture();
			PostMessage(GetParent(hWnd), WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);

			return 0;
		}
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
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
				window->CreateBrowserView();
				PostMessage(hWnd, WM_SIZE, 0, 0);
			}
			return 0;
		}
		break;

		case WM_ERASEBKGND:
		{
			//if (window && window->HasBrowserWindow())
			if (window)
				return 1;
		}
		break;

		case WM_MOVE:
		{
			if (!window) break;

			RECT rect{};
			GetClientRect(hWnd, &rect);

			window->OnSize(SIZE_RESTORED);
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
				return 0;
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
			if (!window) break;
			window->RequestClose();
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


// MainWindow Class Stuff
MainWindow::MainWindowClass MainWindow::MainWindowClass::wndClass;

MainWindow::MainWindowClass::MainWindowClass()
	:
	hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEXA wcex{};
	wcex.cbSize = sizeof(wcex);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = MainWindowWndProc;
	
	//wc.cbClsExtra = 0;
	//wc.cbWndExtra = 0;
	wcex.hInstance = GetInstance();
	//wcex.hIcon = static_cast<HICON>(LoadImage(
	//	GetInstance(), MAKEINTRESOURCE(IDI_ICON1),
	//	IMAGE_ICON, 32, 32, 0
	//));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = GetName();
	//wcex.hIconSm = static_cast<HICON>(LoadImage(
	//	GetInstance(), MAKEINTRESOURCE(IDI_ICON1),
	//	IMAGE_ICON, 16, 16, 0
	//));
	if (!RegisterClassEx(&wcex)) {
		throw AppException(__LINE__, __FILE__, "RegisterClassExA failed!");
	}
}

MainWindow::MainWindowClass::~MainWindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const char* MainWindow::MainWindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE MainWindow::MainWindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}


// MainWindow Stuff
MainWindow::MainWindow()
{
	hWnd_ = CreateWindowEx(
		0,
		MainWindowClass::GetName(),
		"CEF",
		//WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		WS_POPUP | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CLIPCHILDREN,
		200, 50, 1400, 900,
		nullptr,
		nullptr,
		MainWindowClass::GetInstance(),
		this
	);

	if (hWnd_ == nullptr) {
		throw AppException(__LINE__, __FILE__, "CreateWindowExA failed!");
	}

	ShowWindow(hWnd_, SW_SHOWDEFAULT);
	UpdateWindow(hWnd_);
}

MainWindow::~MainWindow()
{
	if (hWnd_) {
		DestroyWindow(hWnd_);
	}
}

void MainWindow::CreateBrowserView()
{
	browser_ = std::make_unique<BrowserView>();
	browser_->CreateBrowserView(hWnd_);
}

void MainWindow::CreateHandle()
{
	// create handle AFTER browser exists
	hHandle_ = CreateWindowExA(
		0,                           // change to this to show the hendleBar
		//WS_EX_TRANSPARENT,			   // change to this to hide the handleBar
		"STATIC",
		nullptr,
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0,
		hWnd_,
		nullptr,
		MainWindowClass::GetInstance(),
		nullptr
	);
	if (!hHandle_) {
		throw AppException(__LINE__, __FILE__, "Failed to create Handle");
	}

	SetWindowLongPtr(hHandle_, GWLP_WNDPROC, (LONG_PTR)HandleWndProc);
	RaiseHandle();
}

void MainWindow::CreateD3DWindow()
{
	d3dWindow_ = std::make_unique<OverlayWindow>();
	d3dWindow_->CreateOverlayWindow(hWnd_);
	PostMessage(hWnd_, WM_SIZE, 0, 0);
}

void MainWindow::SetBrowserHWND(HWND hWndBrowser)
{
	browser_->SetBrowserHWND(hWndBrowser);
}

//bool MainWindow::HasBrowserWindow() const
//{
//	// Return true only if client exists and its browser window is valid
//	if (!client_)
//		return false;
//
//	if (auto browser = client_->GetBrowser())  // safe null check
//		if (auto host = browser->GetHost())   // safe host check
//			return host->GetWindowHandle() != nullptr;
//
//	return false;
//}

void MainWindow::OnSize(WPARAM wParam)
{
	if (wParam == SIZE_MINIMIZED) return;
	assert(hWnd_ && "MainWindow HWND should exist in OnSize");

	RECT rect{};
	GetClientRect(hWnd_, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	if (hHandle_)
	{
		const int buttonWidth = 60;
		const int buttonAreaWidth = 3 * buttonWidth;
		const int titleHeight = 40;
		const int minWidth = buttonWidth;
		int clampedHandleX = std::min(width - buttonAreaWidth - minWidth, handleX);
		int w = width - buttonAreaWidth - clampedHandleX;

		SetWindowPos(hHandle_, HWND_TOP, clampedHandleX, 0, w, titleHeight, SWP_NOACTIVATE);
	}

	if (browser_) {
		browser_->OnSize(width, height);
	}

	if (d3dWindow_) {
		d3dWindow_->OnSize(width, height);
	}
	RaiseHandle();
}

void MainWindow::RequestClose()
{
	if (isClosing_ || !browser_) {
		DestroyWindow(hWnd_);
		return;
	}

	isClosing_ = true;
	browser_->CloseBrowser();
}

void MainWindow::StartFade(FadeAction action)
{
	LONG ex = GetWindowLong(hWnd_, GWL_EXSTYLE);
	SetWindowLong(hWnd_, GWL_EXSTYLE, ex | WS_EX_LAYERED);

	fadeStep = FADE_STEPS;
	fadeAction_ = action;

	SetTimer(hWnd_, TIMER_FADE, 10, NULL);
}
