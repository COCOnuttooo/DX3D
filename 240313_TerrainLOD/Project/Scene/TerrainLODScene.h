#pragma once

class TerrainLODScene : public Scene
{
public:
	TerrainLODScene();
	~TerrainLODScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
private:
	TerrainLOD* terrain;
};