#pragma once
class WaterScene : public Scene
{
public:
	WaterScene();
	~WaterScene();
	// Scene을(를) 통해 상속됨
	void Update() override;

	void PreRender() override;

	void Render() override;

	void PostRender() override;
	void CreateObjects();

private:
	Quad* floor;

	ModelAnimator* knight;

	Sphere* sphere;
	ColliderSphere* colSphere;
	Model* bunny;

	//Reflection* reflection;
	//Refraction* refraction;
	Water* water;
	SkyBox* sky;
	Shadow* shadow;
	//Material* material;
	//VertexBuffer* vertexBuffer;

	
};
