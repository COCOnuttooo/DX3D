#pragma once
class Disc :public GameObject<VertexTextureNormal>
{
	typedef VertexTextureNormal VertexType;
public:
	Disc(float innerRadius = 0.0f, float outerRadius = 1.0f, UINT sliceCount = 20);
	~Disc();
	virtual void CreateMesh() override;

private:

	float innerRadius;
	float outerRadius;
	UINT sliceCount;
	// GameObject��(��) ���� ��ӵ�

};

