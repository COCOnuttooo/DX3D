#pragma once

class PortalQuad : public GameObject<VertexTexture>
{
	typedef VertexTexture VertexType;
public:
	PortalQuad(Vector2 size = { 1, 1 });
	~PortalQuad();

	void Render();

private:
	void CreateMesh() override;

private:

	Vector2 size;

};

