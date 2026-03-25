#pragma once
#include <platform/MyWin.h>
#include <renderer/input/Keyboard.h>
#include <renderer/input/Mouse.h>
#include <renderer/Graphics.h>
#include <memory>

class RendererWindow
{
public:
	RendererWindow(HWND hwndParent);
	~RendererWindow();
	void SetFrame(int left, int top, int width, int height);
	Graphics& Gfx();
public:
	Keyboard kbd;
	Mouse mouse;
private:
	HWND hWnd_ = nullptr; 
	HWND hwndParent_ = nullptr;
	std::unique_ptr<Graphics> gfx_;
};