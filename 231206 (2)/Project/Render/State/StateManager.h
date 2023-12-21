#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singleton;
private:
	StateManager();
	~StateManager();
	void CreateSampler();
private:
	SamplerState* sampler;
};

