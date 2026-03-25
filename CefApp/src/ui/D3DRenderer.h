#pragma once
#include <renderer/RendererWindow.h>
#include <platform/MyTimer.h>
#include <memory>


class D3DRenderer
{
public:
	D3DRenderer(HWND hwndParent);
	~D3DRenderer() = default;
	void Update(float dt);
	void Render();
	void OnResize(int left, int top, int width, int height);
private:
	std::unique_ptr<RendererWindow> wnd_;
	MyTimer timer;
};