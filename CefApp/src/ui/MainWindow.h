#pragma once
#include "../platform/MyWin.h"
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
	void StartFade();
public:
	static constexpr int FADE_STEPS = 15;
	static constexpr int TIMER_FADE = 1;
	int fadeStep = 0;
private:
	HWND hWnd_;
	MyCefClient* client_ = nullptr;
	HWND hWndBrowser_ = nullptr;
	std::string url_ = "http://localhost:5173/"; 
	bool isClosing_ = false;
};

