#pragma once
class Transform2
{
public:
	Transform2();
	virtual ~Transform2();

	void SetWorld();

	void Update();

	void SetParent(Transform* parent);
	void SetPivot(Vector3 pivot) { this->pivot = pivot; }

	Vector3 GetGlobalScale() { return globalScale; }
	Vector3	GetGlobalRotation() { return globalRotation; }
	Vector3	GetGlobalPosition() { return globalPosition; }

	Vector3 GetRightVector() { return right; }
	Vector3 GetUpVector() { return up; }
	Vector3 GetForwardVector() { return forward; }
	Transform* GetParent() { return parent; }
	void Debug();
	void SetName(string name);

	void Save();
	void Load();
	Matrix TestGetWorld() { return world; }
private:
	void UpdateWorldMatrix();

public:
	Vector3 scale = { 1.0f, 1.0f, 1.0f };
	Vector3 rotation = { 0.0f, 0.0f, 0.0f };
	Vector3 translation = { 0.0f, 0.0f, 0.0f };

protected:
	Matrix        world;
	MatrixBuffer* worldBuffer;

	Transform* parent = nullptr;

	Vector3 right, up, forward;

	Vector3 globalScale;
	Vector3	globalRotation;
	Vector3	globalPosition;

	Vector3 pivot;

	string name;

	static UINT index;

	bool isActive = true;
};

