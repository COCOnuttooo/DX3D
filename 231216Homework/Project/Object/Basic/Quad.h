#pragma once

class Quad : public GameObject<VertexTexture>
{
	typedef VertexTexture VertexType;
public:
	Quad(Vector2 size = { 1, 1 });
	~Quad();

	void Render();
	void Debug();

private:
	void CreateMesh() override;

private:

	Vector2 size;

};

