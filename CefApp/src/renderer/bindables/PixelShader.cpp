#include "PixelShader.h"
#include <util/GraphicsThrowMacros.h>

PixelShader::PixelShader(Graphics& gfx, const std::wstring& path)
{
	INFOMAN(gfx);

	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	//GFX_THROW(D3DReadFileToBlob(path.c_str(), &pBlob), "Failed to load pixel shader");
	GFX_THROW(D3DReadFileToBlob(path.c_str(), &pBlob), "Failed to load pixel shader");
	GFX_THROW(GetDevice(gfx)->CreatePixelShader(
		pBlob->GetBufferPointer(), 
		pBlob->GetBufferSize(), 
		nullptr, &pPixelShader), 
		"Failed to create pixel shader");
}

void PixelShader::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}