#include "BrowserView.h"
#include <util/AppThrowMacros.h>
#include <util/DebugLog.h>


BrowserView::BrowserView(HWND hwndParent)
	:
	hwndParent_(hwndParent)
{
	DBG_LOG("Constructing BrowserView");
	client_ = new MyCefClient(hwndParent_);
	RECT rect{};
	GetClientRect(hwndParent_, &rect);
	CefWindowInfo info;
	info.SetAsChild(hwndParent_, CefRect(0, 0,
		rect.right - rect.left, rect.bottom - rect.top));

	if (!CefBrowserHost::CreateBrowser(
			info, client_, url_,
			CefBrowserSettings{},
			nullptr, nullptr)) {
		throw APP_EXCEPT("Failed to create browser");
	}
}

void BrowserView::SetBrowserHWND(HWND hWnd)
{
	hWnd_ = hWnd;
}

void BrowserView::OnSize(int width, int height)
{
	if (!hWnd_ || !hwndParent_) return;

	SetWindowPos(
		hWnd_, 
		nullptr, 
		0, 0,
		width,
		height,
		SWP_NOZORDER | SWP_NOACTIVATE
	);
}

void BrowserView::CloseBrowser()
{
	DBG_LOG("BrowserView::CloseBrowser");
	if (!client_) {
		return;
	}

	if (auto browser = client_->GetBrowser()) {
		browser->GetHost()->CloseBrowser(true);
	}
}