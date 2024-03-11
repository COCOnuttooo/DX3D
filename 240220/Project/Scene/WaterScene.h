#pragma once
class WaterScene : public Scene
{
public:
	WaterScene();
	~WaterScene();
	// Scene��(��) ���� ��ӵ�
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
