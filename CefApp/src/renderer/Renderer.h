#pragma once
#include <platform/MyTimer.h>
#include <renderer/Graphics.h>
#include <memory>


class Renderer
{
public:
	Renderer(HWND hWnd);
	void Update(float dt);
	void Render();
	void OnResize(int width, int height);
private:
	std::unique_ptr<Graphics> gfx_;
	MyTimer timer;
};