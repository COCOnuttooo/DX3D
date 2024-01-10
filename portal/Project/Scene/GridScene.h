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

	// Scene��(��) ���� ��ӵ�
	virtual void P1ReRender() override;

	virtual void P2ReRender() override;
private:
	Grid* grid;



};

