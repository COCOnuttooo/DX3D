#pragma once
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
private:
	Matrix        viewMatrix;
	MatrixBuffer* viewBuffer;
	float moveSpeed = 1.0f;
	float rotateSpeed = 20.0f;

	Vector3 oldPos;
};
