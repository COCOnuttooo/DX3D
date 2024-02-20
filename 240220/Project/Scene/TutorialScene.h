#pragma once

class TutorialScene : public Scene
{
public:
	TutorialScene();
	~TutorialScene();

	void     Update() override;

	void  PreRender() override;
	void     Render() override;
	void PostRender() override;

private:
	Cube* cube;
	Cube* cube2;
};
