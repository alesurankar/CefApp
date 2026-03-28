#include "VertexShader.h"
#include <util/GraphicsThrowMacros.h>


VertexShader::VertexShader(Graphics& gfx, const std::wstring& path)
{
	INFOMAN(gfx);

	//GFX_THROW(D3DReadFileToBlob(path.c_str(), &pBytecodeBlob), "Failed to load vertex shader");
	GFX_THROW(D3DReadFileToBlob(path.c_str(), &pBytecodeBlob), "Failed to load vertex shader");
	GFX_THROW(GetDevice(gfx)->CreateVertexShader(
		pBytecodeBlob->GetBufferPointer(),
		pBytecodeBlob->GetBufferSize(),
		nullptr, &pVertexShader), 
		"Failed to create vertex shader");
}

void VertexShader::Bind(Graphics& gfx) noexcept
{
	GetContext(gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::GetBytecode() const noexcept
{
	return pBytecodeBlob.Get();
}