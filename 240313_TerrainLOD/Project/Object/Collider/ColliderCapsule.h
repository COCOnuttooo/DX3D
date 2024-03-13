#pragma once

class ColliderCapsule : public Collider
{
public:
	ColliderCapsule(float radius = 1.0f, float height = 2.0f, UINT sliceCount = 8, UINT stackCount = 16);
	~ColliderCapsule();

	bool Collision(IN Ray& ray, OUT HitResult* hitResult) override;
	bool Collision(ColliderBox*     other) override;
	bool Collision(ColliderSphere*  other) override;
	bool Collision(ColliderCapsule* other) override;

	float Radius() { return radius * Max(globalScale.x, globalScale.y, globalScale.z); }

	float Height() { return height * globalScale.y; }

private:
	void CreateMesh() override;

private:
	float radius, height;

	UINT stackCount, sliceCount;
};
