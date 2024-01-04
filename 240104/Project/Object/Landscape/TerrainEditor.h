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

	void Picking();	 // Mouse Picking
	void ComputePicking();
	void Debug();
private:
	void CreateMesh() override;
private:
	const float MAX_HEIGHT = 20.0f;
	const UINT  MAX_SIZE   = 256;

	UINT width = MAX_SIZE, height = MAX_SIZE;

	Texture* heightMap;
	Vector3 pickedPos = {};
	const float HEIGHT_SCALE = 20.0f;

	struct InputDesc
	{
		Vector3 v0, v1, v2;
	};
	struct OutputDesc
	{
		int isPicked = false;
		float distance = 0;
	};
	vector<InputDesc> input;
	vector<OutputDesc> output;

	UINT polygonCount = 0;

	StructuredBuffer* structuredBuffer;
	RayBuffer* rayBuffer;

	ComputeShader* computeShader;
};
