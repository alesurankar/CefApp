#pragma once
#include <platform/MyWin.h>
#include <d3d11.h>
#include <wrl.h>

class Graphics
{
public:
	Graphics(HWND hwndOverlay);
	void Clear(float red, float green, float blue) noexcept;
	void Resize(int width, int height);
	void Present();
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
};