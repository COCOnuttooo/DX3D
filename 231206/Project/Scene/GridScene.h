#pragma once
class GridScene : public Scene
{
public:
	GridScene();
	~GridScene();

	// Scene��(��) ���� ��ӵ�
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
private:
	Grid* grid;


};

