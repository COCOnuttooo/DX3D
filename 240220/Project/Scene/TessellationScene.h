#pragma once
class TessellationScene : public Scene
{
public:
	TessellationScene();
	~TessellationScene();

	// Scene��(��) ���� ��ӵ�
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;


private:



};

