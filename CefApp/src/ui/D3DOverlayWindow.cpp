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

void D3DOverlayWindow::SetFrame(int left, int top, int width, int height)
{
	if (!hWnd_) return;
	int offsetX = 60;
	int offsetY = 40;
	int footerY = 29;

	int overlayWidth = width - offsetX;
	int overlayHeight = height - offsetY - footerY;

	SetWindowPos(
		hWnd_,
		HWND_TOP,
		left+offsetX,
		top+offsetY,
		overlayWidth,
		overlayHeight,
		SWP_NOACTIVATE
	);
	renderer_->OnResize(overlayWidth, overlayHeight);
}

void D3DOverlayWindow::Render()
{
	if (renderer_) {
		renderer_->Render();
	}
}