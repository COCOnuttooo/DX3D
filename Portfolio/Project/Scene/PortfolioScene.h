#pragma once
class PortfolioScene : public Scene
{
public:
	PortfolioScene();
	~PortfolioScene();

	void Update() override;

	void PreRender() override;

	void Render() override;

	void PostRender() override;

private:
	Terrain* terrain;
	Onix* onix;
};

