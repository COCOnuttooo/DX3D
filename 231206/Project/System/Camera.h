#pragma once
class Camera : public Transform
{
public:
	Camera();
	~Camera();
	void Update();
	void Set();
private:
	Matrix        viewMatrix;
	MatrixBuffer* viewBuffer;
	float moveSpeed = 1.0f;

	Vector3 oldPos;
};
