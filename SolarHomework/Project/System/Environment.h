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
	Camera* GetCamera() { return mainCamera; }
	Matrix GetProjMatrix() { return projMatrix; }

private:
	Matrix        projMatrix;
	MatrixBuffer* projBuffer;
	LightBuffer* lightBuffer;
	Camera* mainCamera;
};


