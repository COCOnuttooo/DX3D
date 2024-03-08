#pragma once
class FrustumCullingScene : public Scene
{
public:
	FrustumCullingScene();
	~FrustumCullingScene();

	// Scene��(��) ���� ��ӵ�
	void Update() override;

	void PreRender() override;

	void Render() override;

	void PostRender() override;

private:
	vector<Sphere*> spheres;
	CONST UINT SIZE = 10;
};
