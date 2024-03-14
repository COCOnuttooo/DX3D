#pragma once
class DeferredRenderScene : public Scene
{
public:
	DeferredRenderScene();
	~DeferredRenderScene();


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

	Model* bunny;

	GeometryBuffer* gBuffer;

	Material* material;
	VertexBuffer* vertexBuffer;
};

