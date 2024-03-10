#pragma once
class WindEffect : public Particle
{
public:
	WindEffect(wstring file, Transform* target, float tailLength = 1, UINT drawCount = 1000, Vector3 color = Vector3(1,1,1), float turbulence = 0);
	~WindEffect();


	virtual void Update() override;
	virtual void Render() override;
	virtual void Debug()  override;
	void PlayTargeted();
	void TurnOff() { isActive = false; }
	void SetTailLength(float length) { tailLength = length; }
private:
	virtual void SetVertex() override;
private:
	float tailLength;
	vector<VertexTexture> vertices;
	WeatherBuffer* buffer;
	Transform* target;



	// Particle을(를) 통해 상속됨

};
