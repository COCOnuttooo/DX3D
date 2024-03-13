#pragma once

class InstancingScene : public Scene
{
	struct InstanceData
	{
		Matrix transform;

		Vector4 color;
	};
public:
	InstancingScene();
	~InstancingScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	//vector<Quad*> quads;

	const UINT COUNT = 50;

	Quad* quad;

	vector<InstanceData> instanceData;

	VertexBuffer*  instanceBuffer;
};
