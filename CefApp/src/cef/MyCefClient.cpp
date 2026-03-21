#include <platform/MyWin.h>
#include "MyCefClient.h"
#include <ui/MainWindow.h>


bool MyCefClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
	CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
	MainWindow* window = MainWindow::GetWindow(hWndParent_);
	if (!window) return true;
	std::string msgName = message->GetName();

	if (msgName == "SetHandleX")
	{
		auto args = message->GetArgumentList();
		int newX = args->GetInt(0);
		window->titleBar_->handleX = newX;
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
			window->titleBar_->RaiseHandle();
		}
		else if (received == "createD3DWindow") {
			if (!window->GetOverlay()) {
				window->CreateD3DWindow();
			}
		}
		else if (received == "destroyD3DWindow") {
			window->DestroyD3DWindow();
		}
		return true;
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

	if (hWndBrowser && hWndParent_) {
		MainWindow* window = MainWindow::GetWindow(hWndParent_);
		if (window) {
			window->SetBrowserHWND(hWndBrowser);
		}
	}
}

void MyCefClient::OnLoadEnd(CefRefPtr<CefBrowser> pBrowser,
	CefRefPtr<CefFrame> pFrame, int httpStatusCode)
{
	MainWindow* window = MainWindow::GetWindow(hWndParent_);
	ShowWindow(hWndParent_, SW_RESTORE);
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