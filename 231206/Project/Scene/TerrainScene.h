#pragma once
class TerrainScene : public Scene
{
public:
	TerrainScene();
	~TerrainScene();

	void Update() override;

	void PreRender() override;

	void Render() override;

	void PostRender() override;
private:
	Terrain* terrain;

	// Scene을(를) 통해 상속됨

};
