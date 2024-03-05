#include "Framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	CreateSampler();
	CreateRasterizer();
	CreateBlendState();
	CreateDepthStencilState();
}

StateManager::~StateManager()
{
	delete sampler;

	for (RasterizerState* state : rs)
		delete state;
	for (BlendState* state : blendStates)
		delete state;
	for (DepthStencilState* state : depthStencilStates)
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
	rs.emplace_back(new RasterizerState());

	rs[0]->SetFillMode(D3D11_FILL_SOLID);
	rs[1]->SetFillMode(D3D11_FILL_WIREFRAME);
	rs[2]->SetFrontCounterClockWise(true);

	rs[0]->CreateState();
	rs[1]->CreateState();
	rs[2]->CreateState();
}

void StateManager::CreateBlendState()
{
	blendStates.emplace_back(new BlendState);
	blendStates.emplace_back(new BlendState);

	blendStates[0]->SetAlpha(false);
	//blendStates[0]->CreateState();

	blendStates[1]->SetAlpha(true);
	//blendStates[1]->CreateState();

	//AlphaToCoverage
	blendStates.emplace_back(new BlendState);
	blendStates[2]->SetAlphaToCoverage(true);
	//blendStates[2]->CreateState();
	blendStates.emplace_back(new BlendState);
	blendStates[3]->SetAdditive();
}

void StateManager::CreateDepthStencilState()
{
	depthStencilStates.emplace_back(new DepthStencilState());
	depthStencilStates.emplace_back(new DepthStencilState());
	depthStencilStates.emplace_back(new DepthStencilState());

	depthStencilStates[1]->DepthEnable(false);
	depthStencilStates[2]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);
}

void StateManager::EnableWireFrame()
{
	rs[1]->SetState();
}

void StateManager::DisableWireFrame()
{
	rs[0]->SetState();
}

void StateManager::EnableAlpha()
{
	blendStates[1]->SetState();
}

void StateManager::EnableAlphaToCoverage()
{
	blendStates[2]->SetState();

}

void StateManager::EnableAdditive()
{
	blendStates[3]->SetState();
}

void StateManager::DisableAlpha()
{
	blendStates[0]->SetState();

}

void StateManager::EnableDepth()
{
	depthStencilStates[0]->SetState();
}

void StateManager::DisableDepth()
{
	depthStencilStates[1]->SetState();
}

void StateManager::SetFrontCounterClockWise()
{
	rs[2]->SetState();
}

void StateManager::SetFrontClockWise()
{
	rs[0]->SetState();
}

void StateManager::DepthWriteMaskZero()
{
	depthStencilStates[2]->SetState();
}


