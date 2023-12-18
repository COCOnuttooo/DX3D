#pragma once
class BoxScene : public Scene
{
public:
	BoxScene();
	~BoxScene();


	// Scene��(��) ���� ��ӵ�
	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;


private:
	//Quad* quad;
	BoxCube* box;
	Cube* ray;
};
