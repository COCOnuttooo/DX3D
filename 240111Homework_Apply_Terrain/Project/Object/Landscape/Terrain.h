#pragma once
class Terrain : public GameObject<VertexTextureNormalTangent>
{
	typedef VertexTextureNormalTangent VertexType;
public:
	Terrain(wstring heightMapFile);
	~Terrain();
	void Render(D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	void LoadAlphaMap(wstring file);
	void LoadSecondDiffuseMap(wstring file);
	float GetHeight(Vector3 position);
	void LoadMaterial(wstring file);
private:
	void CreateMesh() override;
	void CalculateTangent();
private:
	UINT width = 10, height = 10;
	
	Texture* heightMap;

	const float HEIGHT_SCALE = 20.0f;

	Texture* alphaMap;
	Texture* secondDiffuseMap;


	// GameObject을(를) 통해 상속됨
};

