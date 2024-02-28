#pragma once

class Environment : public Singleton<Environment>
{
	friend class Singleton;
private:
	Environment();
	~Environment();

	void CreatePerspective();

public:
	void Update();
	void Set();

	void Debug();

	Matrix GetPersMatrix() { return persMatrix; }

	Camera* GetMainCamera() { return mainCamera; }

private:
	Matrix        persMatrix;
	MatrixBuffer* persBuffer;

	Camera* mainCamera;

	LightBuffer* lightBuffer;
};
