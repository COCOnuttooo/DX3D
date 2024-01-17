#pragma once
class PortalScene : public Scene
{
public:
	PortalScene();
	~PortalScene();


	// Scene을(를) 통해 상속됨
	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;
	void CalculateMirror();
	// Scene을(를) 통해 상속됨
	virtual void P1ReRender() override;
	virtual void P2ReRender() override;

	XMFLOAT3 ExtractEulerAnglesFromMatrix(const XMMATRIX& mat);
	void BoxMove();
private:
	Vector3 oldPos;
	float moveSpeed = 10;
	float rotateSpeed = 0.01;
	PortalQuad* portal1;
	PortalQuad* portal2;
	TextureCube* cube;
	TextureCube* mainCameraCube;
	TextureCube* mainCameraCubeHead;
	Quad* testQuad;
	Terrain* terrain;

};

