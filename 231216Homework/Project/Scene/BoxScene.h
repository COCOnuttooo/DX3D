#pragma once
class BoxScene : public Scene
{
public:
	BoxScene();
	~BoxScene();


	// Scene을(를) 통해 상속됨
	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;


private:
	//Quad* quad;
	BoxCube* box;
	Cube* ray;
};
