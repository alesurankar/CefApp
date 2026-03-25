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
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	gfx_->BeginFrame(c, c, 1.0f);
	gfx_->DrawTestTriangle(timer.Peek());
	gfx_->EndFrame();
}

void Renderer::OnResize(int width, int height)
{
	gfx_->Resize(width, height);
}
