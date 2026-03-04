#pragma once
#include "../platform/MyWin.h"
#include "../renderer/Renderer.h"

class OverlayWindow
{
public:
	OverlayWindow() = default;
	~OverlayWindow();
	void CreateOverlayWindow(HWND hwnd);
	void OnSize(int parentWidth, int parentHeight);
	void CreateRenderer();
private:
	HWND hWnd_ = nullptr; 
	HWND hwndParent_ = nullptr;
	std::unique_ptr<Renderer> renderer_;
};