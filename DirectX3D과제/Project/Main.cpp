﻿// Project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "Framework.h"
#include "Main.h"

#define MAX_LOADSTRING 100

// 전역 변수:
struct Vertex
{
    Vertex(XMFLOAT3 pos)
        :pos(pos)
    {

    }
    XMFLOAT3 pos = {};

};

struct VertexColor
{
    VertexColor(XMFLOAT3 pos, XMFLOAT4 color)
        :pos(pos), color(color)
    {
    }
    XMFLOAT3 pos;
    XMFLOAT4 color;
};


ID3D11Device*        device;        // 무언가를 만들 때 사용, CPU를 다루는 객체 - Create
ID3D11DeviceContext* deviceContext; // 무언가를 그릴 때 사용, GPU를 다루는 객체 - Set


IDXGISwapChain*         swapChain;       // SwapChain - Double Buffering 을 구현하는 객체
ID3D11RenderTargetView* renderTargetView;// BackBuffer를 관리하는 객체


ID3D11VertexShader* vertexShader;
ID3D11PixelShader* pixelShader;

ID3D11InputLayout* inputLayout;

ID3D11Buffer* vertexBuffer;
ID3D11Buffer* indexBuffer;

ID3D11Buffer* constantBuffer;


vector<VertexColor> vertices;
vector<UINT> indices; 
XMMATRIX world;


float theta = 0;

void Initialize();

void Render();

void Release();

/////////////////////////////



HWND hWnd;

HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.



// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROJECT));

    MSG msg = {};

    // 기본 메시지 루프입니다:
    Initialize();

    while (true)
    {
        if (msg.message == WM_QUIT)
            break;
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            //TODO : Update, Render
            Render();

        }
    }

    Release();
    return (int) msg.wParam;
}



void Initialize()
{
    {
        DXGI_SWAP_CHAIN_DESC desc = {};
        //desc.BufferDesc.Width        = WIN_WIDTH;
        //desc.BufferDesc.Height       = WIN_HEIGHT;
        desc.BufferDesc.RefreshRate.Numerator    = 60 ;
        desc.BufferDesc.RefreshRate.Denominator  = 1;
        desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality   = 0;
        desc.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT; //BackBuffer에대한
        desc.BufferCount  = 1;//BackBuffer에대한
        desc.OutputWindow = hWnd;
        desc.Windowed     = true;
        desc.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
        desc.Flags        = 0;
        
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


        desc[0].SemanticName         = "POSITION";
        desc[0].SemanticIndex        = 0;
        desc[0].Format               = DXGI_FORMAT_R32G32B32_FLOAT;
        desc[0].InputSlot            = 0;
        desc[0].AlignedByteOffset    = 0;
        desc[0].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
        desc[0].InstanceDataStepRate = 0;

        desc[1].SemanticName         = "COLOR";
        desc[1].SemanticIndex        = 0;
        desc[1].Format               = DXGI_FORMAT_R32G32B32A32_FLOAT;
        desc[1].InputSlot            = 0;
        desc[1].AlignedByteOffset    = 12;
        desc[1].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
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
        {XMFLOAT3(-0.5f,+0.5f,0), XMFLOAT4(1.0f,0.0f,0.0f,1.0f)},
        {XMFLOAT3(+0.5f,+0.5f,0), XMFLOAT4(0.0f,1.0f,0.0f,1.0f)},
        {XMFLOAT3(-0.5f,-0.5f,0), XMFLOAT4(0.0f,0.0f,1.0f,1.0f)},
        {XMFLOAT3(+0.5f,-0.5f,0), XMFLOAT4(1.0f,1.0f,1.0f,1.0f)},
        //XMFLOAT3(+0.5f,+0.5f,0),
        //XMFLOAT3(-0.5f,-0.5f,0),

    };
    //backfaceculling

    indices =
    {
        0,1,2,
        2,1,3
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

    //Constant Buffer
    {
        D3D11_BUFFER_DESC bufferDesc = {};
        bufferDesc.ByteWidth = sizeof(XMMATRIX);
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        bufferDesc.CPUAccessFlags = 0;
        bufferDesc.MiscFlags = 0;
        bufferDesc.StructureByteStride = 0;

        device->CreateBuffer(&bufferDesc, nullptr, &constantBuffer);
    }


}

void Render()
{
    float clearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    deviceContext->ClearRenderTargetView(renderTargetView, clearColor); //rendertargetview는 backbuffer를 관리하는 개체
    ////////////////////////
    
    UINT stride = sizeof(VertexColor);
    UINT offset = 0;
    deviceContext->IASetInputLayout(inputLayout);
    deviceContext->UpdateSubresource(constantBuffer, 0, nullptr, &world, 0, 0);
    theta += 0.001;
    world = XMMatrixRotationZ(XMConvertToRadians(theta));
    deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    
    deviceContext->VSSetShader(vertexShader, nullptr, 0);
    deviceContext->PSSetShader(pixelShader, nullptr, 0);

    deviceContext->DrawIndexed(indices.size(),0,0);//Draw Call




    ////////////////////////

    swapChain->Present(0, 0);
}

void Release()
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

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);

    //DX의 Descripter 와 같은 역할
    // 
    
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.
   RECT rect = { 0 ,0, WIN_WIDTH, WIN_HEIGHT };
   AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

   hWnd = CreateWindowW
   (
       szWindowClass, 
       szTitle, 
       WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, 
       rect.right- rect.left, rect.bottom - rect.top, 
       nullptr, nullptr, hInstance, nullptr
   );

   SetMenu(hWnd, nullptr);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
