#pragma once
struct PosDesc
{
	Vector3 pos;
};
class ComputingEffectInstancing : public Particle
{
public:
	ComputingEffectInstancing(wstring file, Transform* target, float tailLength = 1, UINT drawCount = 1000, Vector3 color = Vector3(1, 1, 1), float turbulence = 0);
	~ComputingEffectInstancing();

	static void Delete();
	virtual void Update() override;
	virtual void Render() override;
	virtual void Debug()  override;
	void PlayTargeted();
	void TurnOff() { isActive = false; }
	void SetTailLength(float length) { tailLength = length; }
	void CalculatePos();
	static void CalculatePosInstanced();
	void CreateCompute();
private:
	virtual void SetVertex() override;
private:
	float tailLength;
	vector<VertexTextureIndex> vertices;
	WeatherBuffer* buffer;
	Transform* target;
	PosBuffer* posBuffer;
	AdditionalCumputeBuffer* computeBuffer;
	ComputeShader* computeShader;
	UINT index = 0;


	vector<PosDesc> input;
	vector<PosDesc> output;
	vector<UINT> curIndex;
	static vector<AdditionalCumputeBuffer*> computeBuffers;
	static vector<WeatherBuffer*> buffers;
	static vector<PosBuffer*> posBuffers;

	static vector<Transform*> targets;


	static UINT instanceIndex;
	static UINT dataCounts;
	static StructuredBuffer* structuredBuffer;
	static vector<UINT> indexes;
	static StructuredBuffer* indexStructuredBuffer;
	static StructuredBuffer* weatherStructuredBuffer;
	static StructuredBuffer* computeStructuredBuffer;

	static vector<vector<PosDesc>> inputs;
	static vector<vector<PosDesc>> outputs;
	// Particle을(를) 통해 상속됨

};
