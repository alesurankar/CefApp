#include "MainWindow.h"
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")
#include "../platform/MyWinX.h" 
#include "../cef/MyCefClient.h"

using namespace std::string_literals;

static constexpr const char* wndClassName = "CefApp.MainWindow.Win32";

namespace 
{
	LRESULT CALLBACK HandleWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		static POINT offset{};
		switch (msg)
		{
			case WM_LBUTTONDOWN:
				SetCapture(hwnd);
				GetCursorPos(&offset);
				return 0;
	
			case WM_MOUSEMOVE:
				if (wParam & MK_LBUTTON)
				{
					POINT pt;
					GetCursorPos(&pt);
					HWND hParent = GetParent(hwnd);
					if (hParent)
					{
						RECT rc;
						GetWindowRect(hParent, &rc);
						int dx = pt.x - offset.x;
						int dy = pt.y - offset.y;
						MoveWindow(hParent, rc.left + dx, rc.top + dy,
							rc.right - rc.left, rc.bottom - rc.top, TRUE);
						offset = pt;
					}
				}
				return 0;
	
			case WM_LBUTTONUP:
				ReleaseCapture();
				return 0;

			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				// Fill handle with a solid color, e.g., gray
				FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_BTNFACE + 1));
				EndPaint(hwnd, &ps);
				return 0;
			}
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

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
			break;

			case WM_CREATE:
			{
				MainWindow* window = MainWindow::GetWindow(hWnd);
				if (window) {
					window->CreateBrowser();
					// after main window is created
					HWND hHandle = CreateWindowExA(
						WS_EX_LAYERED,   // layered so can be transparent
						"STATIC",                         // simple class for handle
						nullptr,
						WS_POPUP,                         // popup window
						280, 55, 1130, 40,                     // size & position
						hWnd,                              // parent = main window
						nullptr,
						((LPCREATESTRUCT)lParam)->hInstance,
						nullptr
					);

					// optional transparency
					SetLayeredWindowAttributes(hHandle, 0, 200, LWA_ALPHA);

					SetWindowLongPtr(hHandle, GWLP_WNDPROC, (LONG_PTR)HandleWndProc);
					ShowWindow(hHandle, SW_SHOW);
					PostMessage(hWnd, WM_SIZE, 0, 0);
				}
				return 0;
			}
			break;

			case WM_ERASEBKGND:
			{
				MainWindow* window = MainWindow::GetWindow(hWnd);
				if (window && window->HasBrowserWindow())
					return 1;
			}
			break;

			case WM_TIMER:
			{
				if (wParam == MainWindow::TIMER_FADE) {
					MainWindow* window = MainWindow::GetWindow(hWnd);
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

			case WM_SIZE:
			{
				MainWindow* window = MainWindow::GetWindow(hWnd); 
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

			case WM_NCCALCSIZE:
			{
				if (wParam)
				{
					NCCALCSIZE_PARAMS* p = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);
			
					// shrink client rect by border thickness for resizing
					const int border = 8;
					p->rgrc[0].left += border;
					p->rgrc[0].top += 1;    // little hack to remove white artefact on top
					p->rgrc[0].right -= border;
					p->rgrc[0].bottom -= border;
			
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
				MainWindow* window = MainWindow::GetWindow(hWnd);
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
				MainWindow* window = MainWindow::GetWindow(hWnd);
				SetWindowLongPtr(hWnd, GWLP_USERDATA, 0);
				delete window;
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

	auto* window = new MainWindow(nullptr);
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
	int left = 0;
	int top = 0;
	SetWindowPos(hWndBrowser_, nullptr, left, top,
		rect.right - left, rect.bottom - top,
		SWP_NOZORDER | SWP_NOACTIVATE);
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