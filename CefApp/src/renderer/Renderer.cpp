#include "Renderer.h"

Renderer::Renderer(HWND hWnd)
{
	gfx_ = std::make_unique<Graphics>(hWnd);
}

void Renderer::Update(float dt)
{
	// TODO
}

void Renderer::Render()
{
	float dt = timer.Mark();
	Update(dt);
	gfx_->BeginFrame(0.1f, 0.1f, 0.2f); // dark blue background
	gfx_->EndFrame();
}

void Renderer::OnResize(int width, int height)
{
	gfx_->Resize(width, height);
}
