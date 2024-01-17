#pragma once
class TextureCube;
class PortalQuad : public GameObject<VertexTexture>
{
	typedef VertexTexture VertexType;
public:
	PortalQuad(Vector2 size = { 1, 1 });
	~PortalQuad();

	void Render();
	void Update();
	void SetCamera(Transform* parent);
	void SetCameraDiffuse(wstring file);
	Vector2 GetSize() { return size; }
private:
	void CreateMesh() override;

private:
	TextureCube* cameraBox;
	TextureCube* cameraHead;
	Vector2 size;
	Quad* edge;
};

