#pragma once
class GridScene : public Scene
{
public:
	GridScene();
	~GridScene();

	// Scene을(를) 통해 상속됨
	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;

	// Scene을(를) 통해 상속됨
	virtual void P1ReRender() override;

	virtual void P2ReRender() override;
private:
	Grid* grid;



};

