#pragma once

class LightScene : public Scene
{
public:
	LightScene();
	~LightScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	Quad* floor;

	ModelAnimator* knight;

	Sphere* sphere;

	Model* bunny;

	DepthStencil* depthStencil;
	RenderTarget* renderTarget;

	SkyBox* sky;

	Quad* quad1;
	Quad* quad2;
};
