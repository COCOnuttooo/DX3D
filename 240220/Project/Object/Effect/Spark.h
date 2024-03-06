#pragma once
class Spark : public Particle
{
private:
	struct VertexParticle
	{
		Vector3 position = {};
		Vector2 size = {};
		Vector3 velocity = {};

	};
public:
	Spark(wstring file, bool isAdditive = false);
	~Spark();
	void Update() override;
	void Render() override;
	void Debug() override;

	void Play(Vector3 position) override;


private:

	void SetVertex() override;
	void UpdateParticle();
	// Particle을(를) 통해 상속됨

private:
	vector<VertexParticle> vertices;

	FloatValueBuffer* valueBuffer;
	FloatValueBuffer* startColorBuffer;
	FloatValueBuffer* endColorBuffer;

	float minRadius = 5.0f;
	float maxRadius = 10.0f;

	float minSize = 0.1f;
	float maxSize = 1.0f;
};

