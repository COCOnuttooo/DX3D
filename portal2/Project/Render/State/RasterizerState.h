#pragma once
class RasterizerState
{
public:
	RasterizerState();
	~RasterizerState();

	void SetState();

	void CreateState();

	void SetFillMode(D3D11_FILL_MODE value);
private:
	ID3D11RasterizerState* state;

	D3D11_RASTERIZER_DESC desc = {};
};

