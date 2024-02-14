#pragma once

class Quad : public GameObject<VertexTextureNormalTangent>
{
	typedef VertexTextureNormalTangent VertexType;
public:
	Quad(Vector2 size = { 1, 1 });
	~Quad();
	
	void Render();

private:
	void CreateMesh() override;

private:
	Vector2 size;
};
