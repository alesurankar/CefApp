//#include "../platform/WinWrapper.h"
//#include "MyCefClient.h"
//
//bool MyCefClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
//	CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
//{
//	std::string received = message->GetArgumentList()->GetString(0);
//
//	if (received == "close") {
//		PostMessage(hWndParent_, WM_CLOSE, 0, 0);
//	}
//	else if (received == "minimize") {
//		ShowWindow(hWndParent_, SW_MINIMIZE);
//	}
//	else if (received == "restore") {
//		ShowWindow(hWndParent_, SW_RESTORE);
//	}
//	else if (received == "maximize") {
//		ShowWindow(hWndParent_, SW_MAXIMIZE);
//	}
//	else if (received == "hide") {
//		ShowWindow(hWndParent_, SW_HIDE);
//	}
//	return true;
//}
//
//void MyCefClient::OnAfterCreated(CefRefPtr<CefBrowser> pBrowser)
//{
//	assert(pBrowser);
//	if (!mainBrowser_) {
//		mainBrowser_ = pBrowser;
//	}
//	HWND hWndBrowser = pBrowser->GetHost()->GetWindowHandle();
//	if (hWndBrowser) {
//		RECT rect{};
//		GetClientRect(hWndParent_, &rect);
//		SetWindowPos(hWndBrowser, NULL, 0, 0,
//			rect.right - rect.left,
//			rect.bottom - rect.top, SWP_NOZORDER);
//
//		mainBrowser_->GetMainFrame()->ExecuteJavaScript(
//			"console.log('Step7: Browser initialized!');",
//			mainBrowser_->GetMainFrame()->GetURL(), 0
//		);
//	}
//}
//
//void MyCefClient::OnLoadEnd(CefRefPtr<CefBrowser> pBrowser,
//	CefRefPtr<CefFrame> pFrame, int httpStatusCode)
//{
//	//pFrame->ExecuteJavaScript("alert('Step9: Page loaded!')", pFrame->GetURL(), 0);
//	pFrame->ExecuteJavaScript("console.log('Step9: Page loaded!')", pFrame->GetURL(), 0);
//}
//
//void MyCefClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
//{
//	OutputDebugStringA((std::string("hWndParent_ = ") + std::to_string((uintptr_t)hWndParent_) + "\n").c_str());
//	OutputDebugStringA((std::string("Browser HWND = ") + std::to_string((uintptr_t)browser->GetHost()->GetWindowHandle()) + "\n").c_str());
//	OutputDebugStringA("CEF: OnBeforeClose called\n");
//	/*if (browser == mainBrowser_) {
//		mainBrowser_ = nullptr;
//		DestroyWindow(hWndParent_);
//	}*/
//	if (browser == mainBrowser_) {
//		mainBrowser_ = nullptr;
//		if (hWndParent_) {
//			PostMessage(hWndParent_, WM_CLOSE, 0, 0);
//			hWndParent_ = nullptr;
//		}
//	}
//}
//
////{
////	char buffer[512];
////
////	sprintf_s(buffer, "OnBeforeClose called\n");
////	OutputDebugStringA(buffer);
////
////	sprintf_s(buffer, "hWndParent_ = 0x%p\n", hWndParent_);
////	OutputDebugStringA(buffer);
////
////	sprintf_s(buffer, "Browser HWND = 0x%p\n", browser->GetHost()->GetWindowHandle());
////	OutputDebugStringA(buffer);
////
////	sprintf_s(buffer, "mainBrowser_ = 0x%p, browser == mainBrowser_? %d\n",
////		mainBrowser_.get(), browser == mainBrowser_);
////	OutputDebugStringA(buffer);
////
////	if (browser == mainBrowser_) {
////		mainBrowser_ = nullptr;
////		if (hWndParent_) {
////			sprintf_s(buffer, "Destroying hWndParent_ = 0x%p\n", hWndParent_);
////			OutputDebugStringA(buffer);
////			DestroyWindow(hWndParent_);
////			hWndParent_ = nullptr;
////		}
////	}
////}