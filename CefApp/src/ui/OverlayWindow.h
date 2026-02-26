#pragma once
#include "../platform/MyWin.h"

class OverlayWindow
{
public:
	OverlayWindow() = default;
	~OverlayWindow();
	void CreateOverlayWindow(HWND hwnd);
	void OnSize(int parentWidth, int parentHeight);
private:
	HWND hWnd_ = nullptr; 
	HWND hwndParent_ = nullptr;
};