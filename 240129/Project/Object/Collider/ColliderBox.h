#pragma once
class ColliderBox : public Collider
{
public:
	ColliderBox(Vector3 size = {1,1,1});
	~ColliderBox();

private:
	void CreateMesh() override;
private:

	Vector3 size;

};

