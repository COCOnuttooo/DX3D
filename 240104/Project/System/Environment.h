#pragma once
class Environment : public Singleton<Environment>
{
	friend class Singleton;
private:
	Environment();
	~Environment();

	void CreatePerspective();

public:
	Camera* GetCamera() { return mainCamera; }
	void Update();
	void Set();

	void Debug();

	Matrix GetPersMatrix() { return persMatrix; }
	Camera* GetMainCamera() { return mainCamera; }

private:
	Matrix        persMatrix;
	MatrixBuffer* persBuffer;
	LightBuffer* lightBuffer;
	Camera* mainCamera;
};


