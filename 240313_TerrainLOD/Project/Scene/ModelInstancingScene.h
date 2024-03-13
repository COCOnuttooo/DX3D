#pragma once

class ModelInstancingScene : public Scene
{
public:
	ModelInstancingScene();
	~ModelInstancingScene();

	void Update() override;

	void PreRender() override;

	void Render() override;

	void PostRender() override;

private:
	ModelAnimatorInstancing* model;

	SkyBox* sky;
};
