#pragma once
struct Ray
{
	Vector3 origin;	   //시작점
	Vector3 direction; //방향
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

	Ray ScreenPointToRay(Vector3 screenPoint);
private:
	int thisCount;
	static int cameraCount;
	Matrix        viewMatrix;
	ViewBuffer* viewBuffer;
	float moveSpeed = 1.0f;
	float rotateSpeed = 20.0f;

	Vector3 oldPos;
};
