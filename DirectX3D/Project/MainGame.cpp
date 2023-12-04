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

    ////////////////////////

    UINT stride = sizeof(VertexColor);
    UINT offset = 0;

    DC->IASetInputLayout(inputLayout);
    DC->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    static float angle = 0.0f;
    angle += 0.002;

    DC->VSSetConstantBuffers(0, 1, &constantBuffer);
    DC->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
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
    DC->UpdateSubresource(constantBuffer, 0, nullptr, &data, 0, 0);

    DC->VSSetShader(vertexShader, nullptr, 0);
    DC->PSSetShader(pixelShader, nullptr, 0);

    ///////////////////////////////////////////
    DC->DrawIndexed(indices.size(), 0, 0);//Draw Call
    ///////////////////////////////////////////


}

void MainGame::PreRender()
{
}

void MainGame::PostRender()
{
}

void MainGame::Initialize()
{
    Device::GetInstance();





    //Vertex Shader
    {
        ID3DBlob* blob;
        DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

        D3DCompileFromFile(L"_Shader/Tutorial.hlsl", nullptr, nullptr, "VS", "vs_5_0", flags, 0, &blob, nullptr);

        DEVICE->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader);

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
        DEVICE->CreateInputLayout
        (
            desc,
            layoutSize,
            blob->GetBufferPointer(),
            blob->GetBufferSize(),
            &inputLayout
        );
        blob->Release();
        //DC->IASetInputLayout(inputLayout);

        //DC->VSSetShader(vertexShader, nullptr, 1);

    }
    //pixelShader
    {
        DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

        ID3DBlob* blob;
        D3DCompileFromFile(L"_Shader/Tutorial.hlsl", nullptr, nullptr, "PS", "ps_5_0", flags, 0, &blob, nullptr);
        DEVICE->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader);


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

        DEVICE->CreateBuffer(&desc, &initData, &vertexBuffer);

    }
    //Index Buffer
    {
        D3D11_BUFFER_DESC desc = {};

        desc.ByteWidth = sizeof(UINT) * indices.size();
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

        D3D11_SUBRESOURCE_DATA initData = {};

        initData.pSysMem = indices.data();

        DEVICE->CreateBuffer(&desc, &initData, &indexBuffer);

    }
    //contant buffer
    {
        D3D11_BUFFER_DESC desc = {};

        desc.ByteWidth = sizeof(WVP);
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;


        DEVICE->CreateBuffer(&desc, nullptr, &constantBuffer);

    }
}

void MainGame::Release()
{
    Device::Delete();

    vertexBuffer->Release();
    vertexShader->Release();
    pixelShader->Release();
    inputLayout->Release();
    indexBuffer->Release();
}
