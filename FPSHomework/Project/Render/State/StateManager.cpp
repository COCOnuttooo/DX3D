#include "Framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	CreateSampler();
	CreateRasterizer();
}

StateManager::~StateManager()
{
	delete sampler;

	for (RasterizerState* state : rs)
		delete state;

	rs.clear();
}

void StateManager::CreateSampler()
{
	sampler = new SamplerState();
}

void StateManager::CreateRasterizer()
{
	rs.emplace_back(new RasterizerState());
	rs.emplace_back(new RasterizerState());

	rs[0]->SetFillMode(D3D11_FILL_SOLID);
	rs[1]->SetFillMode(D3D11_FILL_WIREFRAME);

	rs[0]->CreateState();
	rs[1]->CreateState();
}

void StateManager::EnableWireFrame()
{
	rs[1]->SetState();
}

void StateManager::DisableWireFrame()
{
	rs[0]->SetState();
}
