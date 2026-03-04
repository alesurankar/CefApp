#pragma once
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include "Renderer.h"
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
	std::unique_ptr<Renderer> renderer_;
};