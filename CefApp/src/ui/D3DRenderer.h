#pragma once
#include <renderer/RendererWindow.h>
#include <platform/MyTimer.h>
#include <memory>


class D3DRenderer
{
public:
	D3DRenderer(HWND hwndParent);
	~D3DRenderer();
	void Update();
	void Render();
	void Resize(int left, int top, int width, int height);
private:
	std::unique_ptr<RendererWindow> wnd_;
	MyTimer timer;
	std::vector<std::unique_ptr<class Box>> boxes;
	float x1 = 40.0f;
	float y1 = 1.0f;
	float z1 = 0.5f;
private:
	int clientWidth = 0;
	int clientHeight = 0;
};