#pragma once
#include "../platform/MyWin.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "../renderer/Graphics.h"
#include <memory>

class OverlayWindow
{
public:
	OverlayWindow() = default;
	~OverlayWindow();
	void CreateOverlayWindow(HWND hwnd);
	void OnSize(int parentWidth, int parentHeight);
public:
	Keyboard kbd;
	Mouse mouse;
private:
	HWND hWnd_ = nullptr; 
	HWND hwndParent_ = nullptr;
	std::unique_ptr<Graphics> pGfx;
};