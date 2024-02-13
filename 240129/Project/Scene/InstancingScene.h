#pragma once
class InstancingScene : public Scene
{
public:
	InstancingScene();
	~InstancingScene();

	// Scene을(를) 통해 상속됨
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
