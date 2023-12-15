#include "Framework.h"
#include "StateManager.h"

StateManager::StateManager()
{
	CreateSampler();
}

StateManager::~StateManager()
{
	delete sampler;
}

void StateManager::CreateSampler()
{
	sampler = new SamplerState();
}
