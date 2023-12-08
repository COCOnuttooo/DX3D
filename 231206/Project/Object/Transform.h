#pragma once
class Transform
{
public:
	Transform();
	virtual ~Transform();
	void SetWorld();

	void Update();
	Vector3    GetGlobalScale() { return globalScale; };
	Vector3 GetGlobalRotation() { return globalRotation; };
	Vector3      GetGlobalPos() { return globalPosition; };
	Vector3 GetRightVector()   { return right; }
	Vector3 GetUpVector()     { return up; }
	Vector3 GetForwardVector() { return forward; }

	void SetParent(Transform* parent) { this->parent = parent; }
	void SetPivot(Vector3 pivot) { this->pivot = pivot; }
private:

	void UpdateWorldMatrix();
public:
	Vector3		  scale = {1.0f,1.0f,1.0f};
	Vector3    rotation = {0.0f,0.0f,0.0f};
	Vector3 translation = {0.0f,0.0f,0.0f};
protected:

	Matrix		  world;
	MatrixBuffer* worldBuffer;

	Transform* parent = nullptr;
	Vector3 right, up, forward;

	Vector3 globalScale;
	Vector3 globalRotation;
	Vector3 globalPosition;

	Vector3 pivot;
	
};

