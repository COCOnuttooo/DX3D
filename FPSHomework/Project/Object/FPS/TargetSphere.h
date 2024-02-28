#pragma once
class TargetSphere : public Target
{
public:
	TargetSphere();
	~TargetSphere();

	void Update();
	void Render();
	void Debug();
	bool CheckAimed();
	virtual void Respawn(float lifeTime, Vector3 pos, float size);

private:
	Sphere* texture;
};
