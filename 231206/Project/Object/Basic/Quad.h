#pragma once

class Quad : public GameObject<VertexTexture>
{
	typedef VertexTexture VertexType;
public:
	Quad(Vector2 size = { 1, 1 });
	~Quad();

	void Render();

private:
	void CreateMesh() override;

private:
	ID3D11SamplerState* samplerState;

	Vector2 size;

};

