#pragma once

class ColliderSphere : public Collider
{
public:
	ColliderSphere(float radius = 1, UINT stackCount = 15, UINT sliceCount = 15);
	~ColliderSphere();

private:
	
public:
	float radius;
	UINT stackCount;
	UINT sliceCount;

	// Collider��(��) ���� ��ӵ�
	void CreateMesh() override;

};

