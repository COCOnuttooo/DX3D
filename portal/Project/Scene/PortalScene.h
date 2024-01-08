#pragma once
class PortalScene : public Scene
{
public:
	PortalScene();
	~PortalScene();


	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

private:
	PortalQuad* portal1;
	PortalQuad* portal2;
	TextureCube* cube;
	Quad* testQuad;
	Terrain* terrain;
};

