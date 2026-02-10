#include "../platform/MyWin.h"
#include "MyCefClient.h"
#include "../ui/MainWindow.h"
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

void MyCefClient::EnableLayered(HWND hwnd) {
	LONG ex = GetWindowLong(hwnd, GWL_EXSTYLE);
	SetWindowLong(hwnd, GWL_EXSTYLE, ex | WS_EX_LAYERED);
}

void MyCefClient::DwmFadeClose(HWND hwnd) {
	const int steps = 15;
	const int delay = 10; // ms per step (~150ms total)

	for (int i = steps; i >= 0; --i) {
		BYTE alpha = (BYTE)(255 * i / steps);
		SetLayeredWindowAttributes(hwnd, 0, alpha, LWA_ALPHA);
		Sleep(delay);
	}
	PostMessage(hwnd, WM_CLOSE, 0, 0);
}

bool MyCefClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame,
	CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
{
	std::string received = message->GetArgumentList()->GetString(0);

	if (received == "close") {
		//PostMessage(hWndParent_, WM_CLOSE, 0, 0);
		EnableLayered(hWndParent_);
		DwmFadeClose(hWndParent_);
	}
	else if (received == "minimize") {
		ShowWindow(hWndParent_, SW_MINIMIZE);
	}
	else if (received == "resize") {
		WINDOWPLACEMENT wp;
		wp.length = sizeof(WINDOWPLACEMENT);
		if (GetWindowPlacement(hWndParent_, &wp)) {
			if (wp.showCmd == SW_MAXIMIZE) {
				ShowWindow(hWndParent_, SW_RESTORE);
			}
			else {
				ShowWindow(hWndParent_, SW_MAXIMIZE);
			}
		}
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
	if (hWndBrowser && hWndParent_) {
		MainWindow* window = MainWindow::GetWindow(hWndParent_);
		if (window) {
			window->SetBrowserHWND(hWndBrowser);
			PostMessage(hWndParent_, WM_SIZE, 0, 0); 
		}
		mainBrowser_->GetMainFrame()->ExecuteJavaScript(
			"console.log('Browser Count " + std::to_string(browserCount_) + "')",
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