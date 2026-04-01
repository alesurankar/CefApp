#pragma once
#include <platform/MyWin.h>
#include <cef/MyCefClient.h>


class BrowserView
{
public:
	BrowserView(HWND hwndParent);
	~BrowserView() = default;
	void SetBrowserHWND(HWND hWnd);
	void OnSize(int width, int height);
	void CloseBrowser();
private:
	HWND hWnd_ = nullptr;
	HWND hwndParent_ = nullptr;
	CefRefPtr<MyCefClient> client_;
	std::string url_ = "http://localhost:5173/";
};