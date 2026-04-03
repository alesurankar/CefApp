#include "RendererWindow.h"
#include <util/WindowsThrowMacros.h>
#include <cassert>
#include <util/DebugLog.h>


// RendererWindow Class Stuff
RendererWindow::RendererWindowClass RendererWindow::RendererWindowClass::wndClass;

RendererWindow::RendererWindowClass::RendererWindowClass() noexcept
	:
	hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = RendererWindow::HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance(); 
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	RegisterClassEx(&wc);
}

RendererWindow::RendererWindowClass::~RendererWindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const char* RendererWindow::RendererWindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE RendererWindow::RendererWindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}


// RendererWindow Stuff
RendererWindow::RendererWindow(HWND hwndParent)
	:
	hwndParent_(hwndParent)
{
	DBG_LOG("Constructing RendererWindow");
	hWnd_ = CreateWindowExA(
		0,
		RendererWindowClass::GetName(), 
		nullptr,
		WS_POPUP,
		0, 0, 0, 0,
		hwndParent_,
		nullptr, 
		RendererWindowClass::GetInstance(),
		this
	);
	if (hWnd_ == nullptr) {
		throw WND_LAST_EXCEPT();
	}

	ShowWindow(hWnd_, SW_SHOW);
	gfx_ = std::make_unique<Graphics>(hWnd_);
}

RendererWindow::~RendererWindow()
{
	DBG_LOG("Destroying RendererWindow");
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

	int topLeftX = left + offsetX;
	int topLeftY = top + offsetY;
	int windowWidth = width - offsetX;
	int windowHeight = height - offsetY - footerY;
	clientWidth = windowWidth;
	clientHeight = windowHeight;

	SetWindowPos(
		hWnd_,
		HWND_TOP,
		topLeftX,
		topLeftY,
		windowWidth,
		windowHeight,
		SWP_NOACTIVATE
	);
	gfx_->Resize(windowWidth, windowHeight);
}

Graphics& RendererWindow::Gfx()
{
	assert(gfx_ && "gfx_ should never be null");
	return *gfx_;
}


LRESULT CALLBACK RendererWindow::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		RendererWindow* const wnd_ = static_cast<RendererWindow*>(pCreate->lpCreateParams);
		// set WinAPI-managed user data to store ptr to window instance
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wnd_));
		// set message proc to normal (non-setup) handler now that setup is finished
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&RendererWindow::HandleMsgThunk));
		// forward message to window instance handler
		return wnd_->HandleMsg(hWnd, msg, wParam, lParam);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK RendererWindow::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// retrieve ptr to window instance
	RendererWindow* const wnd_ = reinterpret_cast<RendererWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	// forward message to window instance handler
	return wnd_->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT RendererWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KILLFOCUS:
		kbd.ClearState();
		break;

		/*********** KEYBOARD MESSAGES ***********/
	case WM_KEYDOWN:
		// syskey commands need to be handled to track ALT key (VK_MENU) and F10
	case WM_SYSKEYDOWN:
		if (!(lParam & 0x40000000) || kbd.AutorepeatIsEnabled()) // filter autorepeat
		{
			kbd.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		kbd.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		kbd.OnChar(static_cast<unsigned char>(wParam));
		break;
		/*********** END KEYBOARD MESSAGES ***********/
		/************* MOUSE MESSAGES ****************/
	case WM_MOUSEMOVE:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		// in client region -> log move, and log enter + capture mouse (if not previously in window)
		if (pt.x >= 0 && pt.x < clientWidth && pt.y >= 0 && pt.y < clientHeight)
		{
			mouse.OnMouseMove(pt.x, pt.y);
			if (!mouse.IsInWindow())
			{
				SetCapture(hWnd);
				mouse.OnMouseEnter();
			}
		}
		// not in client -> log move / maintain capture if button down
		else
		{
			if (wParam & (MK_LBUTTON | MK_RBUTTON))
			{
				mouse.OnMouseMove(pt.x, pt.y);
			}
			// button up -> release capture / log event for leaving
			else
			{
				ReleaseCapture();
				mouse.OnMouseLeave();
			}
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftPressed(pt.x, pt.y);
		break;
	}
	case WM_RBUTTONDOWN:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightPressed(pt.x, pt.y);
		break;
	}
	case WM_LBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnLeftReleased(pt.x, pt.y);
		// release mouse if outside of window
		if (pt.x < 0 || pt.x >= clientWidth || pt.y < 0 || pt.y >= clientHeight)
		{
			ReleaseCapture();
			mouse.OnMouseLeave();
		}
		break;
	}
	case WM_RBUTTONUP:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		mouse.OnRightReleased(pt.x, pt.y);
		// release mouse if outside of window
		if (pt.x < 0 || pt.x >= clientWidth || pt.y < 0 || pt.y >= clientHeight)
		{
			ReleaseCapture();
			mouse.OnMouseLeave();
		}
		break;
	}
	case WM_MOUSEWHEEL:
	{
		const POINTS pt = MAKEPOINTS(lParam);
		const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		mouse.OnWheelDelta(pt.x, pt.y, delta);
		break;
	}
		/************** END MOUSE MESSAGES **************/
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
