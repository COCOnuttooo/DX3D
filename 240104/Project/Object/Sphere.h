#pragma once
class Sphere : public GameObject<VertexTextureNormalTangent>
{
	typedef VertexTextureNormalTangent VertexType;
public:
	Sphere(float radius = 1.0f, UINT sliceCount = 20, UINT stackCount = 10);
	~Sphere();

private:
	void CreateMesh() override;
	void CalculateTangent();
private:
	float radius;
	UINT sliceCount;
	UINT stackCount;

	// GameObject��(��) ���� ��ӵ�
};

