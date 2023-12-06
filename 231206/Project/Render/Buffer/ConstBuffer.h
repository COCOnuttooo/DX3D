#pragma once

template<typename T>
class ConstBuffer
{
public:
	ConstBuffer(T& data);
	virtual  ~ConstBuffer();
	void SetVSBuffer(UINT slot);
	void SetPSBuffer(UINT slot);

	void UpdateSubresource();
private:
	ID3D11Buffer* constantBuffer;

	T& data;
};

template<typename T>
inline ConstBuffer<T>::ConstBuffer(T& data)
	:data(data)
{
	D3D11_BUFFER_DESC desc = {};

	desc.ByteWidth = sizeof(T);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	DEVICE->CreateBuffer(&desc, nullptr, &constantBuffer);
}

template<typename T>
inline ConstBuffer<T>::~ConstBuffer()
{
	constantBuffer->Release();
}

template<typename T>
inline void ConstBuffer<T>::SetVSBuffer(UINT slot)
{
	UpdateSubresource();
	DC->VSSetConstantBuffers(slot, 1, &constantBuffer);

}

template<typename T>
inline void ConstBuffer<T>::SetPSBuffer(UINT slot)
{
	UpdateSubresource();
	DC->PSSetConstantBuffers(slot, 1, &constantBuffer);

}

template<typename T>
inline void ConstBuffer<T>::UpdateSubresource()
{
	DC->UpdateSubresource(constantBuffer, 0, nullptr, &data, 0, 0);

}
