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

	// GameObject을(를) 통해 상속됨
	virtual void CreateMesh() override;

};
