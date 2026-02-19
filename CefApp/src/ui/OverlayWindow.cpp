#include "OverlayWindow.h"



namespace 
{
	LRESULT CALLBACK OverlayWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
}

OverlayWindow::~OverlayWindow()
{
	if (hWnd_) {
		DestroyWindow(hWnd_);
		hWnd_ = nullptr;
	}
}

void OverlayWindow::CreateOverlayWindow(HWND hwnd)
{
	hWnd_ = CreateWindowExA(
		0,
		"STATIC",
		nullptr,
		WS_CHILD | WS_VISIBLE,
		0, 0, 0, 0,
		hwnd,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);
	SetWindowLongPtr(hWnd_, GWLP_WNDPROC, (LONG_PTR)OverlayWindowProc);
	RaiseOverlayWindow();
}

void OverlayWindow::OnSize(int width, int height)
{
	if (hWnd_)
	{
		SetWindowPos(hWnd_, nullptr, 100, 100,
			width - 200, height - 140,
			SWP_NOZORDER | SWP_NOACTIVATE);
	}
	RaiseOverlayWindow();
}

void OverlayWindow::RaiseOverlayWindow()
{
	if (hWnd_) {
		SetWindowPos(hWnd_, HWND_TOP, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}
}