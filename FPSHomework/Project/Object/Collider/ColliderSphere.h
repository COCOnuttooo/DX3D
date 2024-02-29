#pragma once

class ColliderSphere : public Collider
{
public:
	ColliderSphere(float radius = 1, UINT stackCount = 15, UINT sliceCount = 15);
	~ColliderSphere();

	bool Collision(IN Ray& ray, OUT HitResult* hitResult) override;

	bool Collision(ColliderBox*     other) override;
	bool Collision(ColliderSphere*  other) override;
	bool Collision(ColliderCapsule* other) override;
	float Radius() { return radius * Max(globalScale.x,globalScale.y,globalScale.z); }
private:
	float radius;
	UINT stackCount;
	UINT sliceCount;

	// Collider을(를) 통해 상속됨
	void CreateMesh() override;


	// Collider을(를) 통해 상속됨

};

