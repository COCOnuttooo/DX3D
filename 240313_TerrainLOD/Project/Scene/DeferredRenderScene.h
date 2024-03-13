#pragma once

class DeferredRenderScene : public Scene
{
public:
	DeferredRenderScene();
	~DeferredRenderScene();

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

	Material*     material;
	VertexBuffer* vertexBuffer;
};
