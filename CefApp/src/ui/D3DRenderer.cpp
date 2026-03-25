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
	if (clientWidth < 1 || clientHeight < 1) {
		return;
	}
	const float c = sin(timer.Peek()) / 2.0f + 0.5f;
	wnd_->Gfx().BeginFrame(c, c, 1.0f);
	wnd_->Gfx().DrawTestTriangle(
		timer.Peek(),
		wnd_->mouse.GetPosX() / float(clientWidth * 0.5f) - 1.0f,
		-wnd_->mouse.GetPosY() / float(clientWidth * 0.5f) + 1.0f
	);
	wnd_->Gfx().EndFrame();
}

void D3DRenderer::Resize(int left, int top, int width, int height)
{
	clientWidth = width;
	clientHeight = height;
	wnd_->SetFrame(left, top, width, height);
}
