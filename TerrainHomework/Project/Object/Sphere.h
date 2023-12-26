#pragma once
class Sphere : public GameObject<VertexTextureNormal>
{
	typedef VertexTextureNormal VertexType;
public:
	Sphere(float radius = 1.0f, UINT sliceCount = 20, UINT stackCount = 10);
	~Sphere();

private:
	void CreateMesh() override;
private:
	float radius;
	UINT sliceCount;
	UINT stackCount;

	// GameObject을(를) 통해 상속됨
};

