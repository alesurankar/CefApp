#include "Graphics.h"
#include <sstream>
#include <d3dcompiler.h>
#include <cmath>
#include <DirectXMath.h>
#include <util/GraphicsThrowMacros.h>
#include <util/DebugLog.h>


namespace wrl = Microsoft::WRL;
namespace dx = DirectX;
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

Graphics::Graphics(HWND hwndOverlay)
{
    DBG_LOG("Constructing Graphics");
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
    sd.SampleDesc.Quality = 0;
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
    HRESULT hr;
    // create device and front/back buffers, and swap chain and rendering context
    GFX_THROW_INFO(D3D11CreateDeviceAndSwapChain(
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
    ));

    // gain access to texture subresource in swap chain (back buffer)
    wrl::ComPtr<ID3D11Resource> pBackBuffer;
    GFX_THROW_INFO(pSwap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
    GFX_THROW_INFO(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget));
}

void Graphics::Resize(int width, int height)
{
    HRESULT hr;

    if (width == clientWidth && height == clientHeight) return;
    if (!pSwap || width < 1 || height < 1) return;
    pContext->OMSetRenderTargets(0, nullptr, nullptr);
    clientWidth = width;
    clientHeight = height;
    pTarget.Reset(); // release current RTV
    pDSV.Reset();
    pSwap->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);

    Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
    GFX_THROW_INFO(pSwap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer));
    GFX_THROW_INFO(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget));

    // create depth stensil state
    D3D11_DEPTH_STENCIL_DESC dsDesc = {};
    dsDesc.DepthEnable = TRUE;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
    wrl::ComPtr<ID3D11DepthStencilState> pDSState;
    GFX_THROW_INFO(pDevice->CreateDepthStencilState(&dsDesc, &pDSState));

    // bind depth state
    pContext->OMSetDepthStencilState(pDSState.Get(), 1u);

    // create depth stensil texture
    wrl::ComPtr<ID3D11Texture2D> pDepthStencil;
    D3D11_TEXTURE2D_DESC descDepth = {};
    descDepth.Width = clientWidth;
    descDepth.Height = clientHeight;
    descDepth.MipLevels = 1u;
    descDepth.ArraySize = 1u;
    descDepth.Format = DXGI_FORMAT_D32_FLOAT;
    descDepth.SampleDesc.Count = 1u;
    descDepth.SampleDesc.Quality = 0u;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    GFX_THROW_INFO(pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));

    // create view of depth stensil texture
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
    descDSV.Format = DXGI_FORMAT_D32_FLOAT;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0u;
    GFX_THROW_INFO(pDevice->CreateDepthStencilView(
        pDepthStencil.Get(), &descDSV, &pDSV
    ));

    // bind depth stensil view to OM
    pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pDSV.Get());

    // configure viewport
    D3D11_VIEWPORT vp{};
    vp.Width = static_cast<FLOAT>(clientWidth);
    vp.Height = static_cast<FLOAT>(clientHeight);
    vp.MinDepth = 0;
    vp.MaxDepth = 1;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    pContext->RSSetViewports(1u, &vp);
}

Graphics::~Graphics()
{
    DBG_LOG("Destroying Graphics");

    if (pContext) {
        pContext->ClearState();
        pContext->Flush();
        pContext->OMSetRenderTargets(0, nullptr, nullptr);
    }
    pTarget.Reset();
    pDSV.Reset();
    pSwap.Reset();
    pContext.Reset();
    pDevice.Reset();
}

void Graphics::BeginFrame(float red, float green, float blue) noexcept
{
    const float color[] = { red,green,blue,1.0f };
    pContext->ClearRenderTargetView(pTarget.Get(), color);
    pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::EndFrame()
{
    HRESULT hr;
#ifndef NDEBUG
    infoManager.Set();
#endif
    if (FAILED(hr = pSwap->Present(2u, 0u)))
    {
        if (hr == DXGI_ERROR_DEVICE_REMOVED) {
            throw GFX_DEVICE_REMOVED_EXCEPT(pDevice->GetDeviceRemovedReason());
        }
        else {
            throw GFX_EXCEPT(hr);
        }
    }
}

void Graphics::DrawIndexed(UINT count) noexcept
{
    pContext->DrawIndexed(count, 0u, 0u);
}

void Graphics::SetProjection(DirectX::FXMMATRIX proj) noexcept
{
    projection = proj;
}

DirectX::XMMATRIX Graphics::GetProjection() const noexcept
{
    return projection;
}
