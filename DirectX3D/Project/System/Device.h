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
	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDC() { return deviceContext; }

private:

	ID3D11Device* device;        // ���𰡸� ���� �� ���, CPU�� �ٷ�� ��ü - Create
	ID3D11DeviceContext* deviceContext; // ���𰡸� �׸� �� ���, GPU�� �ٷ�� ��ü - Set


	IDXGISwapChain* swapChain;       // SwapChain - Double Buffering �� �����ϴ� ��ü
	ID3D11RenderTargetView* renderTargetView;// BackBuffer�� �����ϴ� ��ü
};

