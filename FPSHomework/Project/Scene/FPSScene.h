#pragma once
class FPSScene : public Scene
{
public:
	FPSScene();
	~FPSScene();

	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

	void Respawn();

	void CoolTime();

	void AddScore(float score) { this->score += score; }
private:
	float timePassed = 0.0f;
	float score = 0.0f;
	float spawnCoolTime = 0.0f;
	vector<Target*> targets;
	Terrain* terrain;
	Quad* aim;
	// Scene을(를) 통해 상속됨
};

