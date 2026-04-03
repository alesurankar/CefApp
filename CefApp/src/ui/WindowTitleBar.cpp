#include "WindowTitleBar.h"
#include <util/WindowsThrowMacros.h>
#include <util/DebugLog.h>


namespace
{
	LRESULT CALLBACK HandleWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg) {
		case WM_LBUTTONDOWN: {
			ReleaseCapture();
			SendMessage(GetParent(hWnd), WM_NCLBUTTONDOWN, HTCAPTION, 0);
			return 0;
		}
		case WM_LBUTTONDBLCLK: {
			HWND parent = GetParent(hWnd);

			if (IsZoomed(parent))
				ShowWindow(parent, SW_RESTORE);
			else
				ShowWindow(parent, SW_MAXIMIZE);

			return 0;
		}
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}

WindowTitleBar::WindowTitleBar(HWND hwndParent)
	:
	hwndParent_(hwndParent)
{
	DBG_LOG("WindowTitleBar constructor called");
	hWnd_ = CreateWindowExA(
		//0,                           // change to this to show the hendleBar
		WS_EX_TRANSPARENT,			   // change to this to hide the handleBar
		"STATIC",
		nullptr,
		WS_CHILD | WS_VISIBLE | SS_NOTIFY,
		0, 0, 0, 0,
		hwndParent_,
		nullptr,
		GetModuleHandle(nullptr),
		nullptr
	);
	if (hWnd_ == nullptr) {
		throw WND_LAST_EXCEPT();
	}

	SetWindowLongPtr(hWnd_, GWLP_WNDPROC, (LONG_PTR)HandleWndProc);
}

WindowTitleBar::~WindowTitleBar()
{
	DBG_LOG("WindowTitleBar destructor called");
	if (hWnd_) {
		DestroyWindow(hWnd_);
		hWnd_ = nullptr;
	}
}

void WindowTitleBar::OnSize(int parentWidth)
{
	const int buttonWidth = 60;
	const int buttonAreaWidth = 4 * buttonWidth;
	const int titleHeight = 40;
	const int minWidth = buttonWidth;
	int clampedHandleX = std::min(parentWidth - buttonAreaWidth - minWidth, handleX);
	int startHandleX = buttonWidth + clampedHandleX;
	int w = parentWidth - buttonAreaWidth - clampedHandleX;

	SetWindowPos(
		hWnd_,
		HWND_TOP, 
		startHandleX,
		0, 
		w, 
		titleHeight, 
		SWP_NOACTIVATE
	);
}

void WindowTitleBar::RaiseHandle() noexcept
{
	if (hWnd_) {
		SetWindowPos(
			hWnd_,
			HWND_TOP,
			0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}
}