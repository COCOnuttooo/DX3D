#pragma once
class AppliedTerrainScene : public Scene
{
public:
	AppliedTerrainScene();
	~AppliedTerrainScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
private:
	Terrain* terrain;

};
