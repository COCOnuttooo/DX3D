#pragma once
class StateManager : public Singleton<StateManager>
{
	friend class Singleton;
private:
	StateManager();
	~StateManager();
	void CreateSampler();
	void CreateRasterizer();

public:
	void EnableWireFrame();

	void DisableWireFrame();
private:
	SamplerState* sampler;
	vector<RasterizerState*> rs;
};

