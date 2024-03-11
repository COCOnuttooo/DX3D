#pragma once

class GridScene : public Scene
{
public:
	GridScene();
	~GridScene();

	void Update() override;
	
	void PreRender() override;
	void Render() override;
	void PostRender() override;

private:
	Grid* grid;
};
