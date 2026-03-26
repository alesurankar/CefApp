#include "MainWindow.h"
#include <cef/MyCefClient.h>
#include <util/AppException.h>


// Wnd Procedure stuff
namespace
{
	LRESULT CALLBACK MainWindowWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		MainWindow* window = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

		switch (msg) {
		case WM_NCCREATE: {
			CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
			window = static_cast<MainWindow*>(cs->lpCreateParams);

			SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);
			window->AttachHWND(hWnd);
			return TRUE;
		}
		}
		if (!window) {
			return DefWindowProc(hWnd, msg,wParam, lParam);
		}

		switch (msg) {
		case WM_ENTERSIZEMOVE:
			window->isResizing_ = true;
			SetTimer(hWnd, 999, 16, nullptr); // ~60 FPS
			break;

		case WM_EXITSIZEMOVE:
			window->isResizing_ = false;
			KillTimer(hWnd, 999);
			break;

		case WM_ERASEBKGND: {
			if (window && window->HasBrowserWindow()) {
				return 1;
			}
		} break;

		case WM_MOVE: {
			window->OnSize(SIZE_RESTORED);
		} break;

		case WM_SIZE: {
			window->OnSize(wParam);
		} break;

		case WM_GETMINMAXINFO: {
			MINMAXINFO* mmi = reinterpret_cast<MINMAXINFO*>(lParam);
			// Set minimum width and height
			mmi->ptMinTrackSize.x = 520;
			mmi->ptMinTrackSize.y = 360;

			// Maximum size = working area
			HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
			MONITORINFO mi{};
			mi.cbSize = sizeof(mi);

			if (GetMonitorInfo(hMonitor, &mi)) {
				const int border = 4;
				mmi->ptMaxPosition.x = mi.rcWork.left - border;
				mmi->ptMaxPosition.y = mi.rcWork.top - border;
				mmi->ptMaxTrackSize.x = (mi.rcWork.right - mi.rcWork.left) + border * 2;
				mmi->ptMaxTrackSize.y = (mi.rcWork.bottom - mi.rcWork.top) + border * 2;
			}
			return 0;
		}

		case WM_TIMER: {
			if (wParam == 999 && window->isResizing_) {
				// Render continuously while resizing
				if (window->GetD3DRenderer()) {
					window->GetD3DRenderer()->Render();
				}
			}
			else if (wParam == MainWindow::TIMER_FADE) {
				if (window->fadeStep <= 0) {
					KillTimer(hWnd, MainWindow::TIMER_FADE);

					switch (window->fadeAction_) {
					case MainWindow::FadeAction::Close:
						PostMessage(hWnd, WM_CLOSE, 0, 0);
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
						SetLayeredWindowAttributes(hWnd, 0, alpha, LWA_ALPHA);
						window->fadeStep--;
						break;
					default:
						window->fadeStep = 0;
						break;
					}
				}
			}
		} break;

		case WM_NCCALCSIZE: {
			if (wParam) {
				NCCALCSIZE_PARAMS* p = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);
				if (IsZoomed(hWnd)) {
					HMONITOR hMonitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
					MONITORINFO mi{};
					mi.cbSize = sizeof(mi);
					if (GetMonitorInfo(hMonitor, &mi)) {
						RECT& r = p->rgrc[0];
						r = mi.rcWork;
					}
				}
				else {
					const int border = 8;
					p->rgrc[0].left += border;
					p->rgrc[0].top += 1;    // little hack to remove white artefact on top
					p->rgrc[0].right -= border;
					p->rgrc[0].bottom -= border;
				}
			}
			return 0;
		}

		case WM_CLOSE: {
			window->RequestClose();
			return 0;
		}

		case WM_APP + 99: {
			DestroyWindow(hWnd);
			return 0;
		}

		case WM_DESTROY: {
			SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
			PostQuitMessage(0);
			return 0;
		}
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
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
	wcex.style = 0;
	wcex.lpfnWndProc = MainWindowWndProc;

	//wc.cbClsExtra = 0;
	//wc.cbWndExtra = 0;
	wcex.hInstance = GetInstance();
	//wcex.hIcon = static_cast<HICON>(LoadImage(
	//	GetInstance(), MAKEINTRESOURCE(IDI_ICON1),
	//	IMAGE_ICON, 32, 32, 0
	//));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = nullptr;
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
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		//WS_POPUP | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_CLIPCHILDREN,
		200, 50, 1400, 900,
		nullptr,
		nullptr,
		MainWindowClass::GetInstance(),
		this
	);

	if (hWnd_ == nullptr) {
		throw AppException(__LINE__, __FILE__, "CreateWindowExA in MainWindow failed!");
	}
	ShowWindow(hWnd_, SW_MINIMIZE);
	ShowWindow(hWnd_, SW_HIDE);

	CreateWindowTitleBar();
	CreateBrowserView();
}

MainWindow::~MainWindow()
{
	DestroyWindow(hWnd_);
}

void MainWindow::CreateBrowserView()
{
	client_ = new MyCefClient(hWnd_);
	RECT rect{};
	GetClientRect(hWnd_, &rect);
	CefWindowInfo info;
	info.SetAsChild(hWnd_, CefRect(0, 0,
		rect.right - rect.left, rect.bottom - rect.top));
	try {
		CefBrowserHost::CreateBrowser(
			info,
			client_,
			url_,
			CefBrowserSettings{},
			nullptr,
			nullptr
		);
	}
	catch (...) {
		throw AppException(__LINE__, __FILE__, "Failed to create browser");
	}
}

void MainWindow::SetBrowserHWND(HWND hWndBrowser)
{
	hWndBrowser_ = hWndBrowser; 
}

void MainWindow::CreateWindowTitleBar()
{
	titleBar_ = std::make_unique<WindowTitleBar>(hWnd_);
}

void MainWindow::CreateD3DRenderer()
{
	d3dRenderer_ = std::make_unique<D3DRenderer>(hWnd_);
	PostMessage(hWnd_, WM_SIZE, 0, 0);
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
	assert(hWnd_ && "MainWindow HWND should exist in OnSize");

	RECT rect{};
	GetClientRect(hWnd_, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;

	if (titleBar_) {
		titleBar_->OnSize(width);
	}

	if (hWndBrowser_) {
		SetWindowPos(hWndBrowser_, nullptr, 0, 0,
			width, height,
			SWP_NOZORDER | SWP_NOACTIVATE);
	}

	if (d3dRenderer_) {
		POINT topLeft = { rect.left, rect.top };
		ClientToScreen(hWnd_, &topLeft);
		d3dRenderer_->Resize(topLeft.x, topLeft.y, width, height);
	}
}

void MainWindow::RequestClose()
{
	if (isClosing_ || !client_) {
		DestroyWindow(hWnd_);
		return;
	}
	assert(client_ && "RequestClose called but client_ is null");

	isClosing_ = true;
	if (auto browser = client_->GetBrowser()) {
		browser->GetHost()->CloseBrowser(true);
	}
}

void MainWindow::StartFade(FadeAction action, int time)
{
	LONG ex = GetWindowLong(hWnd_, GWL_EXSTYLE);
	SetWindowLong(hWnd_, GWL_EXSTYLE, ex | WS_EX_LAYERED);

	fadeStep = FADE_STEPS;
	fadeAction_ = action;

	SetTimer(hWnd_, TIMER_FADE, time, NULL);
}
