#include "D3DOverlayWindow.h"
#include <util/AppException.h>


namespace 
{
	LRESULT CALLBACK D3DOverlayWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg) {
			case WM_PAINT: {
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				// Fill with semi-transparent gray
				FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_BTNFACE + 1));
				EndPaint(hwnd, &ps);
				return 0;
			}
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

D3DOverlayWindow::D3DOverlayWindow(HWND hwndParent)
	:
	hwndParent_(hwndParent)
{
	hWnd_ = CreateWindowExA(
		WS_EX_LAYERED | WS_EX_NOACTIVATE,
		"STATIC",
		nullptr,
		WS_POPUP,
		0, 0, 0, 0,
		hwndParent,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);
	if (hWnd_ == nullptr) {
		throw AppException(__LINE__, __FILE__, "CreateWindowExA in D3DOverlayWindow failed!");
	}
	SetWindowLongPtr(hWnd_, GWLP_WNDPROC, (LONG_PTR)D3DOverlayWindowProc);
	SetLayeredWindowAttributes(hWnd_, 0, 200, LWA_ALPHA);

	ShowWindow(hWnd_, SW_SHOW);
	renderer_ = std::make_unique<Renderer>(hWnd_);
}

D3DOverlayWindow::~D3DOverlayWindow()
{
	if (hWnd_) {
		DestroyWindow(hWnd_);
		hWnd_ = nullptr;
	}
}

void D3DOverlayWindow::OnSize(int parentWidth, int parentHeight)
{
	if (!hWnd_ || !hwndParent_) return;

	int x = 100;
	int y = 100;
	int width = parentWidth - 200;
	int height = parentHeight - 140;

	POINT pt{ x, y };
	ClientToScreen(hwndParent_, &pt);

	SetWindowPos(
		hWnd_,
		HWND_TOP,
		pt.x,
		pt.y,
		width,
		height,
		SWP_NOACTIVATE
	);
	renderer_->OnResize(width, height);
}
