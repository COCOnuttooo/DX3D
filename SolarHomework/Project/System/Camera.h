#pragma once
class Camera : public Transform2
{
public:
	Camera();
	~Camera();
	void Update();
	void Set();
	void Debug();

	void SaveData();
	void LoadData();
	Matrix GetviewMatrix() { return viewMatrix; }
private:
	Matrix        viewMatrix;
	ViewBuffer* viewBuffer;
	float moveSpeed = 1.0f;
	float rotateSpeed = 20.0f;

	Vector3 oldPos;
};
