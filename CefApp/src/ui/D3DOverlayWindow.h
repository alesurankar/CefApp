#pragma once
#include <platform/MyWin.h>
#include <renderer/input/Keyboard.h>
#include <renderer/input/Mouse.h>
#include <renderer/Renderer.h>
#include <memory>

class D3DOverlayWindow
{
public:
	D3DOverlayWindow(HWND hwndParent);
	~D3DOverlayWindow();
	void OnSize(int parentWidth, int parentHeight);
public:
	Keyboard kbd;
	Mouse mouse;
private:
	HWND hWnd_ = nullptr; 
	HWND hwndParent_ = nullptr;
	std::unique_ptr<Renderer> renderer_;
};