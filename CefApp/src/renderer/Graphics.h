#pragma once
#include <platform/MyWin.h>
#include <util/AppException.h> 
#include <d3d11.h>
#include <wrl.h>

class Graphics
{
public:
	Graphics(HWND hwndOverlay);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics() = default;
	void BeginFrame(float red, float green, float blue) noexcept;
	void EndFrame();
	void Resize(int width, int height);
	void DrawTestTriangle(float  angle);
private:
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
};