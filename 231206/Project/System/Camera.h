#pragma once
class Camera
{
public:
	Camera();
	~Camera();
	void Update();
	void Set();
private:
	Matrix        viewMatrix;
	MatrixBuffer* viewBuffer;
};
