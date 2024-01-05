#pragma once

class Device : public Singleton<Device>
{
	friend class Singleton;
private:
	Device();
	~Device();

	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();

public:
	void ClearRTV();
	void Present();
	void SetMainRTV();
	void SetP1RTV();
	void SetP2RTV();

	ID3D11Device*        GetDevice() { return device;        }
	ID3D11DeviceContext* GetDC()     { return deviceContext; }

private:
	ID3D11Device*           device;         // ���𰡸� ���� �� ���, CPU�� �ٷ�� ��ü - Create�ϴ� ��찡 ����
    ID3D11DeviceContext*    deviceContext;  // ���𰡸� �׸� �� ���, GPU�� �ٷ�� ��ü - Set�ϴ� ��찡 ����

    IDXGISwapChain*         swapChain;          // SwapChain - DoubleBuffering�� �����ϴ� ��ü
	ID3D11RenderTargetView* renderTargetView;   // 
	ID3D11RenderTargetView* p1RTV;   // 
	ID3D11RenderTargetView* p2RTV;   // 

	ID3D11DepthStencilView* depthStencilView;
};
