#pragma once
class ColliderCapsule : public Collider
{
public:
	ColliderCapsule();
	~ColliderCapsule();


	bool Collision(const IN Ray& ray, OUT HitResult* result) override;

	bool Collision(ColliderBox*     other) override;
	bool Collision(ColliderSphere*  other) override;
	bool Collision(ColliderCapsule* other) override;
private:


	// Collider��(��) ���� ��ӵ�
	void CreateMesh() override;

};

