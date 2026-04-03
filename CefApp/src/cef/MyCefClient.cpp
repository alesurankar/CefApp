#include <platform/MyWin.h>
#include "MyCefClient.h"
#include <ui/MainWindow.h>
#include <util/DebugLog.h>


bool MyCefClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
	CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
	DBG_LOG("MyCefClient::OnProcessMessageReceived called");
	MainWindow* window = MainWindow::GetMainWindow(hWndParent_);
	if (!window) return true;
	std::string msgName = message->GetName();

	if (msgName == "SetHandleX")
	{
		auto args = message->GetArgumentList();
		int newX = args->GetInt(0);
		window->GetTitleBar()->handleX = newX;
		PostMessage(hWndParent_, WM_SIZE, 0, 0);
		return true;
	}

	if (msgName == "TestMessage")
	{
		std::string received = message->GetArgumentList()->GetString(0);
		if (received == "close") {
			window->StartFade(MainWindow::FadeAction::Close);
		}
		else if (received == "minimize") {
			ShowWindow(hWndParent_, SW_MINIMIZE);
		}
		else if (received == "resize") {
			WINDOWPLACEMENT wp{};
			wp.length = sizeof(wp);
			if (GetWindowPlacement(hWndParent_, &wp)) {
				if (wp.showCmd == SW_MAXIMIZE) {
					ShowWindow(hWndParent_, SW_RESTORE);
				}
				else {
					ShowWindow(hWndParent_, SW_MAXIMIZE);
				}
			}
		}
		else if (received == "mouseClick") {
			window->GetTitleBar()->RaiseHandle();
		}
		else if (received == "createD3DRenderer") {
			if (!window->GetD3DRenderer()) {
				window->CreateD3DRenderer();
			}
		}
		else if (received == "destroyD3DRenderer") {
			window->DestroyD3DRenderer();
		}
		return true;
	}
	return false;
}

void MyCefClient::OnAfterCreated(CefRefPtr<CefBrowser> pBrowser)
{
	DBG_LOG("MyCefClient::OnAfterCreated called");
	assert(pBrowser);
	browserCount_++;
	if (!mainBrowser_) {
		mainBrowser_ = pBrowser;
	}
	HWND hWndBrowser = pBrowser->GetHost()->GetWindowHandle();

	if (hWndBrowser && hWndParent_) {
		MainWindow* window = MainWindow::GetMainWindow(hWndParent_);
		if (window) {
			window->GetBrowserView()->SetBrowserHWND(hWndBrowser);
		}
	}
}

void MyCefClient::OnLoadEnd(CefRefPtr<CefBrowser> pBrowser,
	CefRefPtr<CefFrame> pFrame, int httpStatusCode)
{
	DBG_LOG("MyCefClient::OnLoadEnd called");
	MainWindow* window = MainWindow::GetMainWindow(hWndParent_);
	ShowWindow(hWndParent_, SW_RESTORE);
}

void MyCefClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	DBG_LOG("MyCefClient::OnBeforeClose called");
	int count = --browserCount_;
	if (count == 0) {
		HWND hwnd = hWndParent_;  // copy first

		mainBrowser_ = nullptr;
		hWndParent_ = nullptr;

		if (hwnd) {
			PostMessage(hwnd, WM_APP + 99, 0, 0);
		}
	}
}