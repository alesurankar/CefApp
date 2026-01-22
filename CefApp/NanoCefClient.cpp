#include "MyWin.h"
#include "NanoCefClient.h"

void NanoCefClient::OnAfterCreated(CefRefPtr<CefBrowser> pBrowser)
{
	assert(pBrowser);
	pBrowser_ = pBrowser;
	HWND hWndBrowser = pBrowser->GetHost()->GetWindowHandle();
	if (hWndBrowser) {
		RECT rect{};
		GetClientRect(hWndParent_, &rect);
		SetWindowPos(hWndBrowser, NULL, 0, 0,
			rect.right - rect.left,
			rect.bottom - rect.top, SWP_NOZORDER);

		// Safe to run JS now, but page may not be fully loaded
		//pBrowser->GetMainFrame()->ExecuteJavaScript(
		//	"alert('Step7: Browser initialized!');",
		//	pBrowser->GetMainFrame()->GetURL(), 0
		//);
		pBrowser->GetMainFrame()->ExecuteJavaScript(
			"console.log('Step7: Browser initialized!');",
			pBrowser->GetMainFrame()->GetURL(), 0
		);
	}
}

void NanoCefClient::OnLoadEnd(CefRefPtr<CefBrowser> pBrowser, 
	CefRefPtr<CefFrame> pFrame, int httpStatusCode)
{
	pFrame->ExecuteJavaScript("alert('Step9: Page loaded!')", pFrame->GetURL(), 0);
	pFrame->ExecuteJavaScript("console.log('Step9: Page loaded!')", pFrame->GetURL(), 0);
}

void NanoCefClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	pBrowser_ = nullptr;
	PostMessage(hWndParent_, WM_CLOSE, 0, 0);
}