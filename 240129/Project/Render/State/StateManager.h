#pragma once

class StateManager : public Singleton<StateManager>
{
	friend class Singleton;
private:
	StateManager();
	~StateManager();

	void CreateSampler();
	void CreateRasterizer();
	void CreateBlendState();
public:

	void  EnableWireFrame();
	void DisableWireFrame();
	void EnableAlpha();
	void DisableAlpha();
private:
	SamplerState* sampler;

	vector<RasterizerState*> rs;
	vector<BlendState*> blendStates;
};
