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
private:
	Matrix        projMatrix;
	MatrixBuffer* projBuffer;

	Camera* mainCamera;
};

