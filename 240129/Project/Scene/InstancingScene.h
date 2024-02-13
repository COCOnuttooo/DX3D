#pragma once
class InstancingScene : public Scene
{
public:
	InstancingScene();
	~InstancingScene();

	// Scene��(��) ���� ��ӵ�
	void Update() override;

	void PreRender() override;

	void Render() override;

	void PostRender() override;

private:
	//vector<Quad*> quads;
	const UINT COUNT = 50;

	Quad* quad;

	vector<Matrix> instanceData;

	VertexBuffer* instanceBuffer;

};
