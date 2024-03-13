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
	void DebugLight(int lightIndex);

	Matrix GetPersMatrix() { return persMatrix; }

	Camera* GetMainCamera() { return mainCamera; }

	LightBuffer* GetLightBuffer() { return lightBuffer; }

private:
	Matrix        persMatrix;
	MatrixBuffer* persBuffer;

	Matrix        orthoMatrix;
	MatrixBuffer* orthoBuffer;

	ViewBuffer*  UIViewBuffer;

	Camera* mainCamera;

	LightBuffer* lightBuffer;
};
