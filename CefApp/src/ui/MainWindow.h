#pragma once
#include "../platform/MyWin.h"
#include <string>

class MyCefClient;

HWND CreateMainWindow(HINSTANCE hInstance);
void CleanupMainWindow(HINSTANCE hInstance);

class MainWindow
{
public:
	enum class FadeAction
	{
		None,
		Close,
		Minimize,
		Maximize,
		Restore
	};
	MainWindow() = default;
	void AttachHWND(HWND hWnd);
	void CreateBrowser();
	static MainWindow* GetWindow(HWND hWnd);
	void OnSize(WPARAM wParam);
	bool HasBrowserWindow() const;
	void SetBrowserHWND(HWND hWndBrowser);
	void RequestClose();
	void StartFade(FadeAction action);
	void SetHandleHWND(HWND h) { hHandle_ = h; }
	HWND GetHandleHWND() const { return hHandle_; }
	void RaiseHandle();
public:
	static constexpr int FADE_STEPS = 15;
	static constexpr int TIMER_FADE = 1;
	int fadeStep = 0;
	bool isMinimized_ = false;
	bool isMaximized_ = false;
	FadeAction fadeAction_ = FadeAction::None;
private:
	HWND hWnd_;
	HWND hHandle_ = nullptr;
	HWND hWndBrowser_ = nullptr;
	MyCefClient* client_ = nullptr;
	std::string url_ = "http://localhost:5173/";
	bool isClosing_ = false;
};

