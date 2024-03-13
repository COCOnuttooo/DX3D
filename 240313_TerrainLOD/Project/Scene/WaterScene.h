#pragma once

class WaterScene : public Scene
{
public:
	WaterScene();
	~WaterScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

	void CreateObjects();

private:
	Quad* floor;
	Collider* collider;
	ModelAnimator* knight;

	Sphere* sphere;

	Model* bunny;

	//Reflection* reflection;
	//Refraction* refraction;

	SkyBox* sky;

	Water* water;

	Shadow* shadow;

	Terrain* terrain;
};
