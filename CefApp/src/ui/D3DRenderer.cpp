#include "D3DRenderer.h"

D3DRenderer::D3DRenderer(HWND hwndParent)
{
	wnd_ = std::make_unique<RendererWindow>(hwndParent);
}

void D3DRenderer::Update(float dt)
{
	// TODO
}

void D3DRenderer::Render()
{
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd_->Gfx().BeginFrame(c, c, 1.0f);
	wnd_->Gfx().DrawTestTriangle(timer.Peek());
	wnd_->Gfx().EndFrame();
}

void D3DRenderer::OnResize(int left, int top, int width, int height)
{
	//gfx_->Resize(width, height);
	wnd_->SetFrame(left, top, width, height);
}
