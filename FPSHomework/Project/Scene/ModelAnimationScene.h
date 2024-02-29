#pragma once

class ModelAnimationScene : public Scene
{
public:
	ModelAnimationScene();
	~ModelAnimationScene();

	void Update() override;

	void PreRender() override;
	void Render() override;
	void PostRender() override;

	void PlayNextClip();
	void PlayClip(int index);

private:
	ModelAnimator* model;

	Model* sword;


};
