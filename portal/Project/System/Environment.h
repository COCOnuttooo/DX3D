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
	void SetP1(Matrix persMat = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f));
	void SetP2(Matrix persMat = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f));

	void Debug();

	Matrix GetPersMatrix() { return persMatrix; }
	Camera* GetMainCamera() { return mainCamera; }
	Camera* GetP1Camera() { return p1Camera; }
	Camera* GetP2Camera() { return p2Camera; }
	void SetPersMatrix(Matrix pers) { this->persMatrix = pers; }
private:
	Matrix        persMatrix;
	MatrixBuffer* persBuffer;
	LightBuffer* lightBuffer;
	Camera* mainCamera;
	Camera* p1Camera;
	Camera* p2Camera;
};


