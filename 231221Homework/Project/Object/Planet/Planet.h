#pragma once
class Planet : public Transform
{
public:
	Planet();
	~Planet();

	void Update();
	void UpdateWorldMatrix();
	void Render();
	void SetInitialTranslation(Vector3 vec = {0,0,0});
	Matrix GetParentMat() { return world; }
	float angle = 0.1;
	float orbitSpeed = 1.0f;
	Vector3 rotation2 = { 0,0,0 };
	Vector3 orbitDir = {1,0,0};
	Vector3 rotationSpeed = {0,0,0};
private:
	TextureCube* cube;
};



