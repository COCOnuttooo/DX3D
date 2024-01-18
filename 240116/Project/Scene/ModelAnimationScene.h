#pragma once
class ModelAnimationScene : public Scene
{
public:
	ModelAnimationScene();
	~ModelAnimationScene();

	// Scene을(를) 통해 상속됨
	void Update() override;

	void PreRender() override;

	void Render() override;

	void PostRender() override;
private:



};

