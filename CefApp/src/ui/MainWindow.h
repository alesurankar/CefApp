#pragma once
#include <string>
#include "../platform/WinWrapper.h"

class MyCefClient;

HWND CreateMainWindow(HINSTANCE hInstance);
void CleanupMainWindow(HINSTANCE hInstance);

class MainWindow
{
public:
	explicit MainWindow(HWND hWnd);
	void AttachHWND(HWND hWnd);
	void CreateBrowser();
	static MainWindow* GetWindow(HWND hWnd);
	void OnSize(WPARAM wParam);
	bool HasBrowserWindow() const;
	void SetBrowserHWND(HWND hWndBrowser);
	void RequestClose();
	CefRefPtr<MyCefClient> GetClient() const;
private:
	HWND hWnd_;
	CefRefPtr<MyCefClient> client_; 
	HWND hWndBrowser_ = nullptr;
	std::string url_ = "http://localhost:5173/"; 
	bool isClosing_ = false;
};

