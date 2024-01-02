#pragma once
struct VertexTerrain
{
	Vector3 pos    = {};
	Vector2 uv     = {};
	Vector3 normal = {};
	Vector4 alpha  = {};

};
class TerrainEditor : public GameObject<VertexTerrain>
{
	typedef VertexTerrain VertexType;
public:
	TerrainEditor();
	~TerrainEditor();

private:
	void CreateMesh() override;

private:
	const float MAX_HEIGHT = 20.0f;
	const UINT  MAX_SIZE   = 256;

	UINT width = MAX_SIZE, height = MAX_SIZE;

	Texture* heightMap;

	const float HEIGHT_SCALE = 20.0f;

};
