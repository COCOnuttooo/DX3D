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
	bool isPlaying = false;
	Knight* player;
	Sphere* target;
	Terrain* terrain;
	Onix* onix;
	Quad* plane;
};

