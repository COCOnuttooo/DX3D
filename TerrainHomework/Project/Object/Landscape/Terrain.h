#pragma once
class Terrain : public GameObject<VertexTextureNormal>
{
	typedef VertexTextureNormal VertexType;
public:
	Terrain(wstring heightMapFile);
	~Terrain();
	float GetHeight(float x, float z);
	float GetWidth() { return width; }
	float GetHeight() { return height; }

private:
	void CreateMesh() override;

private:
	UINT width = 10, height = 10;
	
	Texture* heightMap;

	const float HEIGHT_SCALE = 20.0f;
	// GameObject을(를) 통해 상속됨
};

