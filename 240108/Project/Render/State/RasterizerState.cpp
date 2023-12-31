#include "Framework.h"
#include "RasterizerState.h" 
RasterizerState::RasterizerState()
{
	desc.CullMode = D3D11_CULL_BACK;
	desc.FillMode = D3D11_FILL_SOLID;
}

RasterizerState::~RasterizerState()
{
	state->Release();
}

void RasterizerState::SetState()
{
	DC->RSSetState(state);
}

void RasterizerState::CreateState()
{
	DEVICE->CreateRasterizerState(&desc, &state);
}

void RasterizerState::SetFillMode(D3D11_FILL_MODE value)
{
	desc.FillMode = value;
}
