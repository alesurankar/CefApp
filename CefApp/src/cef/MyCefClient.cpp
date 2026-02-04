#include "../platform/WinWrapper.h"
#include "MyCefClient.h"

bool MyCefClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
	CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
	std::string received = message->GetArgumentList()->GetString(0);

	if (received == "close") {
		PostMessage(hWndParent_, WM_CLOSE, 0, 0);
	}
	else if (received == "minimize") {
		ShowWindow(hWndParent_, SW_MINIMIZE);
	}
	else if (received == "restore") {
		ShowWindow(hWndParent_, SW_RESTORE);
	}
	else if (received == "maximize") {
		ShowWindow(hWndParent_, SW_MAXIMIZE);
	}
	else if (received == "hide") {
		ShowWindow(hWndParent_, SW_HIDE);
	}
	return true;
}

void MyCefClient::OnAfterCreated(CefRefPtr<CefBrowser> pBrowser)
{
	assert(pBrowser);
	browserCount_++;
	if (!mainBrowser_) {
		mainBrowser_ = pBrowser;
	}
	HWND hWndBrowser = pBrowser->GetHost()->GetWindowHandle();
	if (hWndBrowser) {
		PostMessage(hWndParent_, WM_APP + 1, reinterpret_cast<WPARAM>(hWndBrowser), 0);
		/*mainBrowser_->GetMainFrame()->ExecuteJavaScript(
			"console.log('Step7: Browser initialized!');",
			mainBrowser_->GetMainFrame()->GetURL(), 0
		);*/
		mainBrowser_->GetMainFrame()->ExecuteJavaScript(
			"alert('Step7: Browser initialized!');",
			mainBrowser_->GetMainFrame()->GetURL(), 0
		);
		mainBrowser_->GetMainFrame()->ExecuteJavaScript(
			"alert('Brouser Count " + std::to_string(browserCount_) + "')",
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
	int count = --browserCount_;
	if (count == 0) {
		if (hWndParent_) {
			PostMessage(hWndParent_, WM_APP + 99, 0, 0);
			hWndParent_ = nullptr;
		}
		mainBrowser_ = nullptr;
	}
}