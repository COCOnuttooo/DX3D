#pragma once
class Terrain : public GameObject<VertexTextureNormalTangent>
{
	typedef VertexTextureNormalTangent VertexType;
public:
	Terrain(wstring heightMapFile);
	~Terrain();
	float GetHeight(Vector3 position);
private:
	void CreateMesh() override;
	void CalculateTangent();
private:
	UINT width = 10, height = 10;
	
	Texture* heightMap;

	const float HEIGHT_SCALE = 20.0f;
	// GameObject을(를) 통해 상속됨
};

