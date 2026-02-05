#pragma once
#include "../platform/WinWrapper.h"
#include <string>

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
private:
	HWND hWnd_;
	MyCefClient* client_ = nullptr;
	HWND hWndBrowser_ = nullptr;
	std::string url_ = "http://localhost:5173/"; 
	bool isClosing_ = false;
};

