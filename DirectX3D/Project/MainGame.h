#pragma once
class MainGame
{
public:
	MainGame();
	~MainGame();

	void Update(); // ������ �����ϴ� �Լ�
	void Render(); // ȭ���� �����ϴ� �Լ�

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


    ID3D11Device* device;        // ���𰡸� ���� �� ���, CPU�� �ٷ�� ��ü - Create
    ID3D11DeviceContext* deviceContext; // ���𰡸� �׸� �� ���, GPU�� �ٷ�� ��ü - Set


    IDXGISwapChain* swapChain;       // SwapChain - Double Buffering �� �����ϴ� ��ü
    ID3D11RenderTargetView* renderTargetView;// BackBuffer�� �����ϴ� ��ü


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
