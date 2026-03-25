#include "RendererWindow.h"
#include <util/AppException.h>


namespace 
{
	LRESULT CALLBACK RendererWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

RendererWindow::RendererWindow(HWND hwndParent)
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
		throw AppException(__LINE__, __FILE__, "CreateWindowExA in RendererWindow failed!");
	}

	ShowWindow(hWnd_, SW_SHOW);
	gfx_ = std::make_unique<Graphics>(hWnd_);
}

RendererWindow::~RendererWindow()
{
	if (hWnd_) {
		DestroyWindow(hWnd_);
		hWnd_ = nullptr;
	}
}

void RendererWindow::SetFrame(int left, int top, int width, int height)
{
	if (!hWnd_) return;
	int offsetX = 60;
	int offsetY = 40;
	int footerY = 29;

	int windowWidth = width - offsetX;
	int windowHeight = height - offsetY - footerY;

	SetWindowPos(
		hWnd_,
		HWND_TOP,
		left+offsetX,
		top+offsetY,
		windowWidth,
		windowHeight,
		SWP_NOACTIVATE
	);
	gfx_->Resize(windowWidth, windowHeight);
}

Graphics& RendererWindow::Gfx()
{
	if (!gfx_)
	{
		throw; //something
	}
	return *gfx_;
}
