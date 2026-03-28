#pragma once
#include <renderer/RendererWindow.h>
#include <platform/MyTimer.h>
#include <memory>


class D3DRenderer
{
public:
	D3DRenderer(HWND hwndParent);
	~D3DRenderer();
	void Update(float dt);
	void Render();
	void Resize(int left, int top, int width, int height);
private:
	std::unique_ptr<RendererWindow> wnd_; 
	std::vector<std::unique_ptr<class Box>> boxes;
	MyTimer timer;
	int clientWidth = 0;
	int clientHeight = 0;
};