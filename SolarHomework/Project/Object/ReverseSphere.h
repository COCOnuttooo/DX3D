#pragma once
class ReverseSphere : public GameObject<VertexTexture>
{
	typedef VertexTexture VertexType;

public:
	ReverseSphere(float radius = 1.0f, UINT sliceCount = 20, UINT stackCount = 10);
	~ReverseSphere();

private:
	float radius;
	UINT sliceCount;
	UINT stackCount;

	// GameObject��(��) ���� ��ӵ�
	virtual void CreateMesh() override;

};
