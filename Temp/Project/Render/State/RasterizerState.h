#pragma once

class RasterizerState
{
public:
	RasterizerState();
	~RasterizerState();

	void SetState();

	void SetFillMode(D3D11_FILL_MODE value);
	void SetCullMode(D3D11_CULL_MODE value);

	void SetFrontCounterClockWise(bool value);

	void CreateState();

private:
	ID3D11RasterizerState* state;

	D3D11_RASTERIZER_DESC desc = {};
};
