#pragma once
class Terrain : public GameObject<VertexTextureNormal>
{
	typedef VertexTextureNormal VertexType;
public:
	Terrain(wstring heightMapFile);
	~Terrain();
	float GetHeight(Vector3 position);
private:
	void CreateMesh() override;

private:
	UINT width = 10, height = 10;
	
	Texture* heightMap;

	const float HEIGHT_SCALE = 20.0f;
	// GameObject을(를) 통해 상속됨
};

