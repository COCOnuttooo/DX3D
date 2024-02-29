#pragma once
class TempScene : public Scene
{
public:
	TempScene();
	~TempScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

private:

	vector<Robot*> robots;
};

