#pragma once
class DeferredRenderScene : public Scene
{
public:
	DeferredRenderScene();
	~DeferredRenderScene();


	// Scene��(��) ���� ��ӵ�
	void Update() override;

	void PreRender() override;

	void Render() override;

	void PostRender() override;

private:

};

