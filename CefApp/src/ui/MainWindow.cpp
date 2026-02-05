#include "MainWindow.h"
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
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		200, 20, 1360, 1020,
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
	SetWindowPos(hWndBrowser_, nullptr, rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top, 
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