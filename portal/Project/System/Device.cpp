#include "Framework.h"
#include "Device.h"

Device::Device()
{
    CreateDeviceAndSwapChain();
    CreateRenderTargetView();
}

Device::~Device()
{
    device->Release();
    deviceContext->Release();
    swapChain->Release();
    renderTargetView->Release();

    depthStencilView->Release();
    p1RTV->Release();
    p2RTV->Release();
    p1DepthStencilView->Release();
    p2DepthStencilView->Release();
    p1Texture->Release();
    p2Texture->Release();
}

void Device::CreateDeviceAndSwapChain()
{
    {
        DXGI_SWAP_CHAIN_DESC desc = {};

        desc.BufferDesc.Width = WIN_WIDTH;
        desc.BufferDesc.Height = WIN_HEIGHT;
        desc.BufferDesc.RefreshRate.Numerator = 60;
        desc.BufferDesc.RefreshRate.Denominator = 1;
        desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.BufferCount = 1;
        desc.OutputWindow = hWnd;
        desc.Windowed = true;
        desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        desc.Flags = 0;

        D3D11CreateDeviceAndSwapChain
        (
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            0,
            D3D11_CREATE_DEVICE_DEBUG,
            nullptr,
            0,
            D3D11_SDK_VERSION,
            &desc,
            &swapChain,
            &device,
            nullptr,
            &deviceContext
        );
    }
}

void Device::CreateRenderTargetView()
{
    ID3D11Texture2D* backBuffer;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

    D3D11_TEXTURE2D_DESC texDesc = {};
    texDesc.Width = WIN_WIDTH;
    texDesc.Height = WIN_HEIGHT;
    texDesc.MipLevels = 1;
    texDesc.ArraySize = 1;
    texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // ���� ����
    texDesc.SampleDesc.Count = 1;
    texDesc.Usage = D3D11_USAGE_DEFAULT;
    texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
    device->CreateTexture2D(&texDesc, nullptr, &p1Texture);
    device->CreateTexture2D(&texDesc, nullptr, &p2Texture);

    device->CreateRenderTargetView(p1Texture, nullptr, &p1RTV);
    device->CreateRenderTargetView(p2Texture, nullptr, &p2RTV);
    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);

    backBuffer->Release();

    ID3D11Texture2D* depthBuffer;
    ID3D11Texture2D* p1depthBuffer;
    ID3D11Texture2D* p2depthBuffer;

    D3D11_TEXTURE2D_DESC depthDesc = {};

    depthDesc.Width = WIN_WIDTH;
    depthDesc.Height = WIN_HEIGHT;
    depthDesc.MipLevels = 1;
    depthDesc.ArraySize = 1;
    depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthDesc.SampleDesc.Count = 1;
    depthDesc.SampleDesc.Quality = 0;
    depthDesc.Usage = D3D11_USAGE_DEFAULT;
    depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthDesc.CPUAccessFlags = 0;
    depthDesc.MiscFlags = 0;

    device->CreateTexture2D(&depthDesc, nullptr, &depthBuffer);
    device->CreateTexture2D(&depthDesc, nullptr, &p1depthBuffer);
    device->CreateTexture2D(&depthDesc, nullptr, &p2depthBuffer);

    D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};

    dsvDesc.Format = depthDesc.Format;
    dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

    device->CreateDepthStencilView(depthBuffer, &dsvDesc, &depthStencilView);
    device->CreateDepthStencilView(p1depthBuffer, &dsvDesc, &p1DepthStencilView);
    device->CreateDepthStencilView(p2depthBuffer, &dsvDesc, &p2DepthStencilView);

    depthBuffer->Release();
    p1depthBuffer->Release();
    p2depthBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
    deviceContext->OMSetRenderTargets(1, &p1RTV, p1DepthStencilView);
    deviceContext->OMSetRenderTargets(1, &p2RTV, p2DepthStencilView);

    //////////

    //VIEWPORT
    D3D11_VIEWPORT viewPort;
    viewPort.Width = WIN_WIDTH;
    viewPort.Height = WIN_HEIGHT;
    viewPort.TopLeftX = 0.0f;
    viewPort.TopLeftY = 0.0f;
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;

    deviceContext->RSSetViewports(1, &viewPort);
}

void Device::ClearRTV()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView, clearColor);
    deviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Device::ClearPreRTV()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    deviceContext->ClearRenderTargetView(p1RTV, clearColor);
    deviceContext->ClearDepthStencilView(p1DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
    deviceContext->ClearRenderTargetView(p2RTV, clearColor);
    deviceContext->ClearDepthStencilView(p2DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Device::Present()
{
    swapChain->Present(0, 0);
}

void Device::SetMainRTV()
{
    deviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);

}

void Device::SetP1RTV()
{
    deviceContext->OMSetRenderTargets(1, &p1RTV, p1DepthStencilView);

}

void Device::SetP2RTV()
{
    deviceContext->OMSetRenderTargets(1, &p2RTV, p2DepthStencilView);

}
