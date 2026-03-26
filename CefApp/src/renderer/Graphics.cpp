#include "Graphics.h"
#include <sstream>
#include <d3dcompiler.h>
#include <cmath>
#include <DirectXMath.h>

namespace wrl = Microsoft::WRL;
namespace dx = DirectX;
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

#define GFX_THROW(hrcall, note) \
    do { \
        HRESULT hrTemp = (hrcall); \
        if (FAILED(hrTemp)) \
            throw AppException(__LINE__, __FILE__, note); \
    } while(0)

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
    const float color[] = { red,green,blue,1.0f };
    pContext->ClearRenderTargetView(pTarget.Get(), color);
    pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::EndFrame()
{
    HRESULT hr;
    if (FAILED(hr = pSwap->Present(2u, 0u)))
    {
        if (hr == DXGI_ERROR_DEVICE_REMOVED)
        {
            throw AppException(__LINE__, __FILE__, "Device removed: " + std::to_string(pDevice->GetDeviceRemovedReason()));
        }
        else
        {
            throw AppException(__LINE__, __FILE__, "Failed to present frame. HRESULT: " + std::to_string(hr));
        }
    }
}

void Graphics::Resize(int width, int height)
{
    if (width == clientWidth && height == clientHeight) return;
    if (!pSwap || width < 1 || height < 1) return;
    pContext->OMSetRenderTargets(0, nullptr, nullptr);
    clientWidth = width;
    clientHeight = height;
    pTarget.Reset(); // release current RTV
    pDSV.Reset();
    pSwap->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);

    Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;
    GFX_THROW(pSwap->GetBuffer(0, __uuidof(ID3D11Resource), &pBackBuffer), "Failed to get back buffer after resize");
    GFX_THROW(pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &pTarget), "Failed to create RTV after resize");

    // create depth stensil state
    D3D11_DEPTH_STENCIL_DESC dsDesc = {};
    dsDesc.DepthEnable = TRUE;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
    wrl::ComPtr<ID3D11DepthStencilState> pDSState;
    GFX_THROW(pDevice->CreateDepthStencilState(&dsDesc, &pDSState), "");

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
    GFX_THROW(pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil), "");

    // create view of depth stensil texture
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
    descDSV.Format = DXGI_FORMAT_D32_FLOAT;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0u;
    GFX_THROW(pDevice->CreateDepthStencilView(
        pDepthStencil.Get(), &descDSV, &pDSV
    ), "");

    // bind depth stensil view to OM
    pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pDSV.Get());
}

void Graphics::DrawTestTriangle(float angle, float x, float z)
{
    struct Vertex
    {
        struct
        {
            float x;
            float y;
            float z;
        } pos;
    };

    // create vertex buffer (1 2d triangle at center of screen)
    Vertex vertices[] =
    {
        { -1.0f, -1.0f, -1.0f },
        {  1.0f, -1.0f, -1.0f },
        { -1.0f,  1.0f, -1.0f },
        {  1.0f,  1.0f, -1.0f },
        { -1.0f, -1.0f,  1.0f },
        {  1.0f, -1.0f,  1.0f },
        { -1.0f,  1.0f,  1.0f },
        {  1.0f,  1.0f,  1.0f },
    };
    wrl::ComPtr<ID3D11Buffer> pVertexBuffer;
    D3D11_BUFFER_DESC bd = {};
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.CPUAccessFlags = 0u;
    bd.MiscFlags = 0u;
    bd.ByteWidth = sizeof(vertices);
    bd.StructureByteStride = sizeof(Vertex);
    D3D11_SUBRESOURCE_DATA sd = {};
    sd.pSysMem = vertices;
    GFX_THROW(pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer), "Failed to create vertex buffer");

    // Bind vertex buffer to pipeline
    const UINT stride = sizeof(Vertex);
    const UINT offset = 0u;
    pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);

    // create index buffer
    const unsigned short indices[] =
    {
        0,2,1, 2,3,1,
        1,3,5, 3,7,5,
        2,6,3, 3,6,7,
        4,5,7, 4,7,6,
        0,4,2, 2,4,6,
        0,1,4, 1,5,4,
    };
    wrl::ComPtr<ID3D11Buffer> pIndexBuffer;
    D3D11_BUFFER_DESC ibd = {};
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.CPUAccessFlags = 0u;
    ibd.MiscFlags = 0u;
    ibd.ByteWidth = sizeof(indices);
    ibd.StructureByteStride = sizeof(unsigned short);
    D3D11_SUBRESOURCE_DATA isd = {};
    isd.pSysMem = indices;
    GFX_THROW(pDevice->CreateBuffer(&ibd, &isd, &pIndexBuffer), "Failed to create index buffer");

    // bind index buffer
    pContext->IASetIndexBuffer(pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u);

    // create constant buffer for transformation matrix
    struct ConstantBuffer
    {
        dx::XMMATRIX transform;
    };
    const ConstantBuffer cb =
    {
        {
            dx::XMMatrixTranspose(
                dx::XMMatrixRotationZ(angle) *
                dx::XMMatrixRotationX(angle) *
                dx::XMMatrixTranslation(x,0.0f,z + 4.0f) *
                dx::XMMatrixPerspectiveLH(1.0f,3.0f / 4.0f,0.5f,10.0f)
            )
        }
    };
    wrl::ComPtr<ID3D11Buffer> pConstantBuffer;
    D3D11_BUFFER_DESC cbd;
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbd.MiscFlags = 0u;
    cbd.ByteWidth = sizeof(cb);
    cbd.StructureByteStride = 0u;
    D3D11_SUBRESOURCE_DATA csd = {};
    csd.pSysMem = &cb;
    GFX_THROW(pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer), "Failed to create constant buffer");

    // bind constant buffer to vertex shader
    pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());

    struct ConstantBuffer2
    {
        struct
        {
            float r;
            float g;
            float b;
            float a;
        } face_colors[6];
    };
    const ConstantBuffer2 cb2 =
    {
        {
            {1.0f,0.0f,1.0f},
            {1.0f,0.0f,0.0f},
            {0.0f,1.0f,0.0f},
            {0.0f,0.0f,1.0f},
            {1.0f,1.0f,0.0f},
            {0.0f,1.0f,1.0f},
        }
    };
    wrl::ComPtr<ID3D11Buffer> pConstantBuffer2;
    D3D11_BUFFER_DESC cbd2;
    cbd2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd2.Usage = D3D11_USAGE_DEFAULT;
    cbd2.CPUAccessFlags = 0u;
    cbd2.MiscFlags = 0u;
    cbd2.ByteWidth = sizeof(cb2);
    cbd2.StructureByteStride = 0u;
    D3D11_SUBRESOURCE_DATA csd2 = {};
    csd2.pSysMem = &cb2;
    GFX_THROW(pDevice->CreateBuffer(&cbd2, &csd2, &pConstantBuffer2), "Failed to create constant buffer");

    // bind constant buffer to pixel shader
    pContext->PSSetConstantBuffers(0u, 1u, pConstantBuffer2.GetAddressOf());


    // create pixel shader
    wrl::ComPtr<ID3D11PixelShader> pPixelShader;
    wrl::ComPtr<ID3DBlob> pBlob;
    GFX_THROW(D3DReadFileToBlob(L"shader_bins/PixelShader.cso", &pBlob), "Failed to load pixel shader");
    GFX_THROW(pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader), "Failed to create pixel shader");

    // bind pixel shader
    pContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);

    // create vertex shader
    wrl::ComPtr<ID3D11VertexShader> pVertexShader;
    GFX_THROW(D3DReadFileToBlob(L"shader_bins/VertexShader.cso", &pBlob), "Failed to load vertex shader");
    GFX_THROW(pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader), "Failed to create vertex shader");
    
    // bind vertex shader
    pContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);

    // input (vertex) layout (2d position only)
    wrl::ComPtr<ID3D11InputLayout> pInputLayout;
    const D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
    };
    GFX_THROW(pDevice->CreateInputLayout(
        ied, (UINT)std::size(ied),
        pBlob->GetBufferPointer(),
        pBlob->GetBufferSize(),
        &pInputLayout
    ), "Failed to create input layout");

    // bind vertex layout
    pContext->IASetInputLayout(pInputLayout.Get());

    // Set primitive topology to triangle list (groups of 3 vertices)
    pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // configure viewport
    D3D11_VIEWPORT vp{};
    vp.Width = static_cast<FLOAT>(clientWidth);
    vp.Height = static_cast<FLOAT>(clientHeight);
    vp.MinDepth = 0;
    vp.MaxDepth = 1;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    pContext->RSSetViewports(1u, &vp);


    pContext->DrawIndexed((UINT)std::size(indices), 0u, 0u);
}