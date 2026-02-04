#include "../platform/WinWrapper.h"
#include "Client.h"


void Client::OnAfterCreated(CefRefPtr<CefBrowser> pBrowser)
{
	mainBrowser_ = pBrowser;  // stores temporary pBrowser from UI thread to mainBrowser_ on Win32 thread

	HWND hWndBrowser = pBrowser->GetHost()->GetWindowHandle();
	PostMessage(hWndParent_, WM_APP + 1, reinterpret_cast<WPARAM>(hWndBrowser), 0);
	mainBrowser_->GetMainFrame()->ExecuteJavaScript(
		"console.log('Step7: Browser initialized!');",
		mainBrowser_->GetMainFrame()->GetURL(), 0
	);
}












bool Client::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
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
