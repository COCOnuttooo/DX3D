#include "Framework.h"
#include "Device.h"
Device::Device()
{
   CreateDeviceAndSwapChain();
   CreateRenderTargetView();
}

Device::~Device()
{
    device->Release();        // ���𰡸� ���� �� ���, CPU�� �ٷ�� ��ü - Create
    deviceContext->Release(); // ���𰡸� �׸� �� ���, GPU�� �ٷ�� ��ü - Set
    swapChain->Release();       // SwapChain - Double Buffering �� �����ϴ� ��ü
    renderTargetView->Release();// BackBuffer�� �����ϴ� ��ü
}

void Device::CreateDeviceAndSwapChain()
{
    DXGI_SWAP_CHAIN_DESC desc = {};
    //desc.BufferDesc.Width        = WIN_WIDTH;
    //desc.BufferDesc.Height       = WIN_HEIGHT;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //BackBuffer������
    desc.BufferCount = 1;//BackBuffer������
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

void Device::CreateRenderTargetView()
{
    ID3D11Texture2D* backBuffer;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

    device->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView);

    backBuffer->Release();

    deviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);

    /////////////////ViewPort
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

    deviceContext->ClearRenderTargetView(renderTargetView, clearColor); //rendertargetview�� backbuffer�� �����ϴ� ��ü

}

void Device::Present()
{
    swapChain->Present(0, 0);

}
