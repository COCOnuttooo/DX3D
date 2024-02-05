#pragma once

class Environment : public Singleton<Environment>
{
	friend class Singleton;
private:
	Environment();
	~Environment();

	void CreatePerspective();
	void CreateOrthographic();
public:
	void Update();
	void Set();
	void PostSet();

	void Debug();

	Matrix GetPersMatrix() { return persMatrix; }

	Camera* GetMainCamera() { return mainCamera; }

private:
	Matrix        persMatrix;
	MatrixBuffer* persBuffer;

	Matrix        orthoMatrix;
	MatrixBuffer* orthoBuffer;

	ViewBuffer* UIViewBuffer;

	Camera* mainCamera;

	LightBuffer* lightBuffer;
};
