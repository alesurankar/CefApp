#pragma once
#include "../platform/MyWin.h"

class OverlayWindow
{
public:
	OverlayWindow() = default;
	~OverlayWindow();
	void CreateOverlayWindow(HWND hwnd);
	void OnSize(int width, int hight);
	void RaiseOverlayWindow();
private:
	HWND hWnd_ = nullptr;
};