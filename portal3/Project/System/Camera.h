#pragma once
struct Ray
{
	Vector3 origin;	   //������
	Vector3 direction; //����
};
class Camera : public Transform
{
public:
	Camera();
	~Camera();
	void Update();
	void Set();
	void Debug();

	void SaveData();
	void LoadData();
	void SetViewMatrix(Matrix view) { this->viewMatrix = view; }
	Ray ScreenPointToRay(Vector3 screenPoint);
	void SetFixViewMatrix(Matrix view) { this->fixViewMatrix = view; }
private:
	void UpdateWorldMatrix() override;
private:

	Matrix fixViewMatrix;
	int thisCount;
	static int cameraCount;
	Matrix        viewMatrix;
	ViewBuffer* viewBuffer;
	float moveSpeed = 1.0f;
	float rotateSpeed = 20.0f;

	Vector3 oldPos;
};
