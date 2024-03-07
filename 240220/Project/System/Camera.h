#pragma once

//struct Ray
//{
//	Vector3 origin;    //시작점
//	Vector3 direction; //방향
//};

class Camera : public Transform
{
public:
	Camera();
	~Camera();

	void Update();
	void Set();

	void SetView();

	void Debug();

	void   FreeMode();
	void TargetMode();

	void SaveData();
	void LoadData();

	struct Ray ScreenPointToRay(Vector3 screenPoint);
	Vector3 WorldToScreenPos(Vector3 worldPos);
	void SetTarget(Transform* target) { this->target = target; }

	ViewBuffer* GetViewBuffer() { return viewBuffer; }
	//Frustum
public:
	bool PointInFrustum(Vector3 point);
	bool SphereInFrustum(Vector3 center, float radius);

private:
	void CalculateFrustum();



private:
	Matrix      viewMatrix;
	ViewBuffer* viewBuffer;

	float   moveSpeed =  1.0f;
	float rotateSpeed = 0.01;

	Vector3 oldPos;

	Transform* target = nullptr;

	float distance = 20.0f;
	float height = 5.0f;
	float moveDamping = 30.0f;
	float rotDamping = 30.0f;

	float rotY = 0.0f;
	float destRotX = 0.0f;
	float destRotY = 0.0f;

	Vector3 destPos;
	Vector3 focusOffset;

	Matrix rotMatrix;

	//Frustum Culling
	XMVECTOR planes[6];

	float a, b, c, d;
};
