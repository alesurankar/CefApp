#include "D3DOverlayWindow.h"
#include <util/AppException.h>


namespace 
{
	LRESULT CALLBACK D3DOverlayWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg) {
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
			// TODO forward to renderer
			break;
		}
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}

D3DOverlayWindow::D3DOverlayWindow(HWND hwndParent)
	:
	hwndParent_(hwndParent)
{
	hWnd_ = CreateWindowExA(
		0,
		"STATIC",
		nullptr,
		WS_POPUP,
		0, 0, 0, 0,
		hwndParent_,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);
	if (hWnd_ == nullptr) {
		throw AppException(__LINE__, __FILE__, "CreateWindowExA in D3DOverlayWindow failed!");
	}

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

void D3DOverlayWindow::Render()
{
	if (renderer_) {
		renderer_->Render();
	}
}