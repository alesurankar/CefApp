#include "D3DRenderer.h"
#include <renderer/drawables/Box.h>
#include <memory>


D3DRenderer::D3DRenderer(HWND hwndParent)
{
	wnd_ = std::make_unique<RendererWindow>(hwndParent);
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 1.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.08f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (auto i = 0; i < 180; i++) {
		boxes.push_back(std::make_unique<Box>(
			wnd_->Gfx(), rng, adist,
			ddist, odist, rdist
		));
	}
	wnd_->Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

D3DRenderer::~D3DRenderer()
{}

void D3DRenderer::Update()
{
	if (wnd_->kbd.KeyIsPressed('W')) {
		y1 -= 0.02f;
	}
	if (wnd_->kbd.KeyIsPressed('S')) {
		y1 += 0.02f;
	}
	if (wnd_->kbd.KeyIsPressed('A')) {
		x1 += 0.02f;
	}
	if (wnd_->kbd.KeyIsPressed('D')) {
		x1 -= 0.02f;
	}
	if (wnd_->kbd.KeyIsPressed(VK_SHIFT)) {
		z1 += 0.002f;
	}
	if (wnd_->kbd.KeyIsPressed(VK_SPACE)) {
		z1 -= 0.002f;
	}
}

void D3DRenderer::Render()
{
	if (clientWidth < 1 || clientHeight < 1) {
		return;
	}

	wnd_->Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(y1, 3 * y1 / 4, z1, x1));
	auto dt = timer.Mark();
	wnd_->Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	for (auto& b : boxes) {
		b->Update(dt);
		b->Draw(wnd_->Gfx());
	}
	wnd_->Gfx().EndFrame();
}

void D3DRenderer::Resize(int left, int top, int width, int height)
{
	clientWidth = width;
	clientHeight = height;
	wnd_->SetFrame(left, top, width, height);
}
