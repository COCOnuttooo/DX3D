#pragma once
class SolarBackgroundQuad :public GameObject<VertexTexture>
{
	typedef VertexTexture VertexType;

public:
	SolarBackgroundQuad(Vector2 size = { 1, 1 });
	~SolarBackgroundQuad();
	void Render();

private:
	void CreateMesh() override;
	Vector2 size;

};
