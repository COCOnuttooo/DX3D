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

	ID3D11Device* device;        // 무언가를 만들 때 사용, CPU를 다루는 객체 - Create
	ID3D11DeviceContext* deviceContext; // 무언가를 그릴 때 사용, GPU를 다루는 객체 - Set


	IDXGISwapChain* swapChain;       // SwapChain - Double Buffering 을 구현하는 객체
	ID3D11RenderTargetView* renderTargetView;// BackBuffer를 관리하는 객체
};

