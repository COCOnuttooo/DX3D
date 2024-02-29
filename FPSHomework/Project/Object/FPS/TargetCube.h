#pragma once
class TargetCube : public Target
{
public:
	TargetCube();
	~TargetCube();
	void Update();
	void Render();
	virtual void Respawn(float lifeTime, Vector3 pos, float size);
	bool CheckAimed();
private:
	TextureCube* texture;
};
