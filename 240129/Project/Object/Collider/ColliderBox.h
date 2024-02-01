#pragma once

class ColliderBox : public Collider
{
public:
	struct OBB
	{
		Vector3 axis[3];
		Vector3 halfSize;
	};
public:
	ColliderBox(Vector3 size = {1,1,1});
	~ColliderBox();

	bool Collision(const IN Ray& ray, OUT HitResult* result) override;

	bool Collision(ColliderBox*     other) override;
	bool Collision(ColliderSphere*  other) override;
	bool Collision(ColliderCapsule* other) override;

	OBB GetOBB();

	bool SeparatedAxis(Vector3 distance, Vector3 axis, OBB box1, OBB box2);
	


private:
	void CreateMesh() override;
private:

	Vector3 size;


	// Collider을(를) 통해 상속됨
};

