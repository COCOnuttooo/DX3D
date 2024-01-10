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
private:
	PortalQuad* portal1;
	PortalQuad* portal2;
	TextureCube* cube;
	TextureCube* mainCameraCube;
	Quad* testQuad;
	Terrain* terrain;

};

