#include "MyWin.h"
#include "MyCefClient.h"

void MyCefClient::OnAfterCreated(CefRefPtr<CefBrowser> pBrowser)
{
	assert(pBrowser);
	if (!mainBrowser_) {
		mainBrowser_ = pBrowser;
	}
	HWND hWndBrowser = pBrowser->GetHost()->GetWindowHandle();
	if (hWndBrowser) {
		RECT rect{};
		GetClientRect(hWndParent_, &rect);
		SetWindowPos(hWndBrowser, NULL, 0, 0,
			rect.right - rect.left,
			rect.bottom - rect.top, SWP_NOZORDER);

		// Safe to run JS now, but page may not be fully loaded
		//mainBrowser_->GetMainFrame()->ExecuteJavaScript(
		//	"alert('Step7: Browser initialized!');",
		//	mainBrowser_->GetMainFrame()->GetURL(), 0
		//);
		mainBrowser_->GetMainFrame()->ExecuteJavaScript(
			"console.log('Step7: Browser initialized!');",
			mainBrowser_->GetMainFrame()->GetURL(), 0
		);
	}
}

void MyCefClient::OnLoadEnd(CefRefPtr<CefBrowser> pBrowser,
	CefRefPtr<CefFrame> pFrame, int httpStatusCode)
{
	//pFrame->ExecuteJavaScript("alert('Step9: Page loaded!')", pFrame->GetURL(), 0);
	pFrame->ExecuteJavaScript("console.log('Step9: Page loaded!')", pFrame->GetURL(), 0);
}

void MyCefClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	if (browser == mainBrowser_) {
		mainBrowser_ = nullptr;
		PostMessage(hWndParent_, WM_CLOSE, 0, 0);
	}
}