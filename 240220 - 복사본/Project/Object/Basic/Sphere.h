#pragma once

class Sphere : public GameObject<VertexTextureNormalTangent>
{
	typedef VertexTextureNormalTangent VertexType;
public:
	Sphere(float radius = 1.0f, UINT sliceCount = 20, UINT stackCount = 10);
	
	~Sphere();
	float GetRadius() { return radius * Max(scale.x, scale.y, scale.z); }

private:
	void CreateMesh() override;

	void CalculateTangent();

private:
	float radius;
	UINT  sliceCount;
	UINT  stackCount;
};
