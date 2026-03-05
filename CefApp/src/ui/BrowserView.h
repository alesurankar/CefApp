#pragma once
#include <platform/MyWin.h>
//#include <cef/config/MyCefConfig_base.h>
#include <cef/MyCefClient.h>


//class MyCefClient;

class BrowserView
{
public:
	BrowserView() = default;
	~BrowserView() = default;
	void CreateBrowserView(HWND hwndParent);
	void SetBrowserHWND(HWND hWnd);
	void OnSize(int width, int height);
	void CloseBrowser();
private:
	HWND hWnd_ = nullptr;
	HWND hwndParent_ = nullptr;
	CefRefPtr<MyCefClient> client_;
	std::string url_ = "http://localhost:5173/";
};