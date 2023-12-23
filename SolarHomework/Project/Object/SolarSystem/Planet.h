#pragma once
class Planet : public Transform
{
public:
	Planet();
	~Planet();

	void Update();
	void UpdateWorldMatrix();
	void Render();
	void SetInitialTranslation(Vector3 vec = { 0,0,0 });
	void SetOrbit(Vector3 vec);
	Matrix GetParentMat() { return world; }
	float angle = 0.01;
	Vector3 rotation2 = { 0,0,0 };
	Vector3 orbitDir = { 1,0,0 };
	Vector3 rotationSpeed = { 0,0,0 };

	void SetDiffuseMap(wstring file);
	float orbitSpeed = 0.01f;
	void SetSpecularMap(wstring file);
	void SetOrbitSpeedScale(float value) { orbitSpeed /= value; }
	void SetSpeedScale(float value) { orbitSpeedScale = value; }
private:
	float orbitSpeedScale = 1;
	Sphere* sphere;
	LightBuffer* lightBuffer;

};



