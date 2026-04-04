#pragma once
#include "ConstantBuffers.h"
#include <renderer/drawables/Drawable.h>
#include <DirectXMath.h>

class TransformCbuf : public Bindable
{
public:
	TransformCbuf(Graphics& gfx, const Drawable& parent);
	void Bind(Graphics& gfx) noexcept override;
	static void Reset() { pVcbuf.reset(); }
private:
	static std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> pVcbuf;
	const Drawable& parent;
};