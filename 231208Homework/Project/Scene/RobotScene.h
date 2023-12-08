#pragma once
class RobotScene : public Scene
{
public:
	RobotScene();
	~RobotScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

private:

	HomeworkBot* bot;
};
