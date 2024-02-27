#pragma once

class LightScene : public Scene
{
public:
	LightScene();
	~LightScene();


	// Scene을(를) 통해 상속됨
	void Update() override;

	void PreRender() override;

	void Render() override;

	void PostRender() override;

private:
	Quad* floor;
	
	
	SkyBox* sky;
	ModelAnimator* knight;

	Sphere* sphere;

	Model* bunny;

	DepthStencil* depthStencil;
	RenderTarget* renderTarget;

	Quad* quad1;
	Quad* quad2;
}; 

