#pragma once
struct VertexTerrain
{
	Vector3 pos    = {};
	Vector2 uv     = {};
	Vector3 normal = {};
	Vector4 alpha  = {};
	Vector3 tangent = {};

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
	void Render(D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) override;
	void Update();
private:
	void CalculateTangent();
	void CreateMesh() override;
	void AdjustHeight();
	void AdjustAlpha();

	void SaveHeightMap();
	void LoadHeightMap();
	void CreateCompute();
	void UpdateMesh();
private:
	const float MAX_HEIGHT = 20.0f;
	const UINT  MAX_SIZE   = 256;

	UINT width = MAX_SIZE, height = MAX_SIZE;

	Texture* heightMap;
	Vector3 pickedPos = {};
	const float HEIGHT_SCALE = 20.0f;
	float adjustValue = 10.0f;
	UINT pickedIndex = 0;
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

	BrushBuffer* brushBuffer;

	//Texture Splatting

	Texture* alphaMap;
	Texture* secondDiffuseMap;


};
