#pragma once
class RobotScene : public Scene
{
public:
	RobotScene();
	~RobotScene();

	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

private:

	HomeworkBot* bot;
};
