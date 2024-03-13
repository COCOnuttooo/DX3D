#pragma once

class DepthStencil
{
public:
	DepthStencil(UINT width = WIN_WIDTH, UINT height = WIN_HEIGHT, bool isStencil = false);
	~DepthStencil();

	void ClearDSV();

	ID3D11DepthStencilView*   GetDSV() { return dsv; }
	ID3D11ShaderResourceView* GetSRV() { return srv; }

private:
	void CreateTexture();
	void CreateDSV();
	void CreateSRV();

private:
	UINT width, height;

	ID3D11Texture2D* texture;

	ID3D11DepthStencilView*   dsv;
	ID3D11ShaderResourceView* srv;

	bool isStencil = false;
};
