#pragma once

//struct Ray
//{
//	Vector3 origin;    //������
//	Vector3 direction; //����
//};

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

	struct Ray ScreenPointToRay(Vector3 screenPoint);
	Vector3 WorldToScreenPos(Vector3 worldPos);

private:
	Matrix      viewMatrix;
	ViewBuffer* viewBuffer;

	float   moveSpeed =  5.0f;
	float rotateSpeed = 20.0f;

	Vector3 oldPos;
};
