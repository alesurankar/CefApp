#include "Graphics.h"
#include <sstream>

namespace wrl = Microsoft::WRL;
#pragma comment(lib, "d3d11.lib")

#define GFX_THROW(hrcall, note) \
    do { HRESULT hrTemp = (hrcall); if (FAILED(hrTemp)) throw AppException(__LINE__, __FILE__, note); } while(0)

Graphics::Graphics(HWND hwndOverlay)
{
    // Minimal Direct3D11 initialization
    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 0;
    sd.BufferDesc.RefreshRate.Denominator = 0;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.SampleDesc.Count = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 1;
    sd.OutputWindow = hwndOverlay;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = 0;

    UINT swapCreateFlags = 0u;
#ifndef NDEBUG
    swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    // create device and front/back buffers, and swap chain and rendering context
    GFX_THROW(D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        swapCreateFlags,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &sd,
        &pSwap,
        &pDevice,
        nullptr,
        &pContext
    ), "Failed to create D3D11 device and swap chain");

    // gain access to texture subresource in swap chain (back buffer)
    wrl::ComPtr<ID3D11Resource> pBackBuffer;
    GFX_THROW(pSwap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer), "Failed to get back buffer");
    GFX_THROW(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget), "Failed to create RTV");
}

void Graphics::BeginFrame(float red, float green, float blue) noexcept
{
    if (pContext && pTarget)
    {
        const float color[] = { red,green,blue,1.0f };
        pContext->ClearRenderTargetView(pTarget.Get(), color);
    }
}

void Graphics::EndFrame()
{
    if (pSwap)
    {
        HRESULT hr = pSwap->Present(1, 0);
        if (FAILED(hr))
            throw AppException(__LINE__, __FILE__, "Failed to present frame");
    }
}

void Graphics::Resize(int width, int height)
{
    if (!pSwap) return;

    pTarget.Reset(); // release current RTV
    pSwap->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);

    Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
    GFX_THROW(pSwap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer), "Failed to get back buffer after resize");
    GFX_THROW(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget), "Failed to create RTV after resize");
}
