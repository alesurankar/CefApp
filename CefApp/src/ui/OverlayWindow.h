#pragma once
#include <renderer/input/Keyboard.h>
#include <renderer/input/Mouse.h>
#include <renderer/Renderer.h>
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