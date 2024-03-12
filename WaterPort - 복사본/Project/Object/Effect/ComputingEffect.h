#pragma once
class ComputingEffect : public Particle
{
public:
	ComputingEffect(wstring file, Transform* target, float tailLength = 1, UINT drawCount = 1000, Vector3 color = Vector3(1, 1, 1), float turbulence = 0);
	~ComputingEffect();


	virtual void Update() override;
	virtual void Render() override;
	virtual void Debug()  override;
	void PlayTargeted();
	void TurnOff() { isActive = false; }
	void SetTailLength(float length) { tailLength = length; }
	void CalculatePos();

	void CreateCompute();
private:
	virtual void SetVertex() override;
private:
	float tailLength;
	vector<VertexTextureIndex> vertices;
	WeatherBuffer* buffer;
	Transform* target;
	PosBuffer* posBuffer;
	ComputeShader* computeShader;

	struct PosDesc
	{
		Vector3 pos;
	};

	vector<PosDesc> input;
	vector<PosDesc> output;
	StructuredBuffer* structuredBuffer;

	// Particle을(를) 통해 상속됨

};
