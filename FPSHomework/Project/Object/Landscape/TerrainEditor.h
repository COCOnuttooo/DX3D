#pragma once

struct VertexTerrain
{
	Vector3 pos     = {};
	Vector2 uv      = {};
	Vector3 normal  = {};
	Vector4 alpha   = {};

	Vector3 tangent = {};
};

enum EditorType
{
	HEIGHT, ALPHA
};

class TerrainEditor : public GameObject<VertexTerrain>
{
	typedef VertexTerrain VertexType;
public:
	TerrainEditor();
	~TerrainEditor();

	void        Picking(); //Mouse Picking
	void ComputePicking();

	void Debug();
	
	void Update();
	void Render(D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST) override;

private:
	void CreateMesh() override;

	void AdjustHeight();
	void AdjustAlpha();

	void SaveHeightMap();
	void LoadHeightMap();

	void SaveAlphaMap();
	void LoadAlphaMap();

	void UpdateMesh();

	void CreateCompute();

private:
	const float MAX_HEIGHT = 20.0f;
	const UINT  MAX_SIZE   = 256;

	UINT width = MAX_SIZE, height = MAX_SIZE;

	Texture* heightMap;

	const float HEIGHT_SCALE = 20.0f;

	float adjustValue = 10.0f;

	Vector3 pickedPos = {};

	//Compute Shader
	struct InputDesc
	{
		Vector3 v0, v1, v2;
	};

	struct OutputDesc
	{
		int   isPicked = false;
		float distance = 0;
	};

	vector< InputDesc>  input;
	vector<OutputDesc> output;

	UINT polygonCount = 0;

	StructuredBuffer* structuredBuffer;

	  RayBuffer*   rayBuffer;
	BrushBuffer* brushBuffer;

	ComputeShader* computeShader;

	//Texture Splatting

	Texture* alphaMap;

	Texture* secondDiffuseMap;

	EditorType type = HEIGHT;
};
