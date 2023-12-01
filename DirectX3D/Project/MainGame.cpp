#include "Framework.h"
#include "MainGame.h"

MainGame::MainGame()
{
	Initialize();
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Update()
{
}

void MainGame::Render()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView, clearColor); //rendertargetview는 backbuffer를 관리하는 개체
    ////////////////////////

    UINT stride = sizeof(VertexColor);
    UINT offset = 0;

    deviceContext->IASetInputLayout(inputLayout);
    deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    static float angle = 0.0f;
    angle += 0.002;

    deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    WVP data;
    data.worldMatrix = XMMatrixRotationRollPitchYaw(angle, angle, 0);
    XMVECTOR eye = XMVectorSet(+3, +3, -3, 0);
    XMVECTOR focus = XMVectorSet(0, 0, 0, 0);
    XMVECTOR up = XMVectorSet(+0, +1, 0, 0);

    data.viewMatrix = XMMatrixLookAtLH(eye, focus, up);
    data.projMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV2, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);
    data.worldMatrix = XMMatrixTranspose(data.worldMatrix);
    data.viewMatrix = XMMatrixTranspose(data.viewMatrix);
    data.projMatrix = XMMatrixTranspose(data.projMatrix);
    //rotation = XMMatrixRotationZ(angle);
    deviceContext->UpdateSubresource(constantBuffer, 0, nullptr, &data, 0, 0);

    deviceContext->VSSetShader(vertexShader, nullptr, 0);
    deviceContext->PSSetShader(pixelShader, nullptr, 0);

    deviceContext->DrawIndexed(indices.size(), 0, 0);//Draw Call





    ////////////////////////

    swapChain->Present(0, 0);
}

void MainGame::PreRender()
{
}

void MainGame::PostRender()
{
}

void MainGame::Initialize()
{
    {
        DXGI_SWAP_CHAIN_DESC desc = {};
        //desc.BufferDesc.Width        = WIN_WIDTH;
        //desc.BufferDesc.Height       = WIN_HEIGHT;
        desc.BufferDesc.RefreshRate.Numerator = 60;
        desc.BufferDesc.RefreshRate.Denominator = 1;
        desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT; //BackBuffer에대한
        desc.BufferCount = 1;//BackBuffer에대한
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

    //Vertex Shader
    {
        ID3DBlob* blob;
        DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

        D3DCompileFromFile(L"_Shader/Tutorial.hlsl", nullptr, nullptr, "VS", "vs_5_0", flags, 0, &blob, nullptr);

        device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader);

        D3D11_INPUT_ELEMENT_DESC desc[2] = {};


        desc[0].SemanticName = "POSITION";
        desc[0].SemanticIndex = 0;
        desc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
        desc[0].InputSlot = 0;
        desc[0].AlignedByteOffset = 0;
        desc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        desc[0].InstanceDataStepRate = 0;

        desc[1].SemanticName = "COLOR";
        desc[1].SemanticIndex = 0;
        desc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        desc[1].InputSlot = 0;
        desc[1].AlignedByteOffset = 12;
        desc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        desc[1].InstanceDataStepRate = 0;



        UINT layoutSize = ARRAYSIZE(desc);
        device->CreateInputLayout
        (
            desc,
            layoutSize,
            blob->GetBufferPointer(),
            blob->GetBufferSize(),
            &inputLayout
        );
        blob->Release();
        //deviceContext->IASetInputLayout(inputLayout);

        //deviceContext->VSSetShader(vertexShader, nullptr, 1);

    }
    //pixelShader
    {
        DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

        ID3DBlob* blob;
        D3DCompileFromFile(L"_Shader/Tutorial.hlsl", nullptr, nullptr, "PS", "ps_5_0", flags, 0, &blob, nullptr);
        device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader);


        blob->Release();
    }
    //Create Vertex

    vertices =
    {
        {XMFLOAT3(-0.5f,+0.5f,-0.5), XMFLOAT4(1.0f,0.0f,0.0f,1.0f)},
        {XMFLOAT3(+0.5f,+0.5f,-0.5), XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
        {XMFLOAT3(-0.5f,-0.5f,-0.5), XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
        {XMFLOAT3(+0.5f,-0.5f,-0.5), XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},

        {XMFLOAT3(-0.5f,+0.5f,0.5f), XMFLOAT4(0.0f,0.0f,0.0f,1.0f)},
        {XMFLOAT3(+0.5f,+0.5f,0.5f), XMFLOAT4(0.5f,0.7f,0.9f,1.0f)},
        {XMFLOAT3(-0.5f,-0.5f,0.5f), XMFLOAT4(0.1f,0.9f,1.0f,1.0f)},
        {XMFLOAT3(+0.5f,-0.5f,0.5f), XMFLOAT4(1.0f,0.6f,0.5f,1.0f)},
        //XMFLOAT3(+0.5f,+0.5f,0),
        //XMFLOAT3(-0.5f,-0.5f,0),

    };
    //backfaceculling

    indices =
    {
        0,1,2,
        2,1,3,

        //back
        5,4,7,
        7,4,6,

        //left
        4,0,6,
        6,0,2,
        // right

        1,5,3,
        3,5,7,

        //Top

        0,4,1,
        1,4,5,

        //Bottom

        2,3,6,
        6,3,7
    };
    //Vertex Buffer
    {
        D3D11_BUFFER_DESC desc = {};

        desc.ByteWidth = sizeof(VertexColor) * vertices.size();
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

        D3D11_SUBRESOURCE_DATA initData = {};

        initData.pSysMem = vertices.data();

        device->CreateBuffer(&desc, &initData, &vertexBuffer);

    }
    //Index Buffer
    {
        D3D11_BUFFER_DESC desc = {};

        desc.ByteWidth = sizeof(UINT) * indices.size();
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA initData = {};

        initData.pSysMem = indices.data();

        device->CreateBuffer(&desc, &initData, &indexBuffer);

    }
    //contant buffer
    {
        D3D11_BUFFER_DESC desc = {};

        desc.ByteWidth = sizeof(WVP);
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;


        device->CreateBuffer(&desc, nullptr, &constantBuffer);

    }
}

void MainGame::Release()
{
    device->Release();        // 무언가를 만들 때 사용, CPU를 다루는 객체 - Create
    deviceContext->Release(); // 무언가를 그릴 때 사용, GPU를 다루는 객체 - Set
    swapChain->Release();       // SwapChain - Double Buffering 을 구현하는 객체
    renderTargetView->Release();// BackBuffer를 관리하는 객체
    vertexBuffer->Release();
    vertexShader->Release();
    pixelShader->Release();
    inputLayout->Release();
    indexBuffer->Release();
}
