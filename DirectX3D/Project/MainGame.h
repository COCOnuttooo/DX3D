#pragma once
class MainGame
{
public:
	MainGame();
	~MainGame();

	void Update(); // 정보를 갱신하는 함수
	void Render(); // 화면을 갱신하는 함수

	void PreRender();
	void PostRender();
private:
	void Initialize();
	void Release();

private:
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


    ID3D11Device* device;        // 무언가를 만들 때 사용, CPU를 다루는 객체 - Create
    ID3D11DeviceContext* deviceContext; // 무언가를 그릴 때 사용, GPU를 다루는 객체 - Set


    IDXGISwapChain* swapChain;       // SwapChain - Double Buffering 을 구현하는 객체
    ID3D11RenderTargetView* renderTargetView;// BackBuffer를 관리하는 객체


    ID3D11VertexShader* vertexShader;
    ID3D11PixelShader* pixelShader;

    ID3D11InputLayout* inputLayout;

    ID3D11Buffer* vertexBuffer;
    ID3D11Buffer* indexBuffer;

    vector<VertexColor> vertices;
    vector<UINT> indices;

    ///

    struct WVP
    {
        XMMATRIX worldMatrix;
        XMMATRIX viewMatrix;
        XMMATRIX projMatrix;
    };


    ID3D11Buffer* constantBuffer;


};
