#pragma once
class BoxScene : public Scene
{
public:
	BoxScene();
	~BoxScene();

	virtual void Update() override;

	virtual void PreRender() override;

	virtual void Render() override;

	virtual void PostRender() override;

private:
	Crate* box;
	Crate* box2;
	Crate* box3;
};

