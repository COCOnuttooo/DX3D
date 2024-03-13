#pragma once

class Character : public ColliderCapsule
{
public:
	Character(string name, float radius = 1.0f, float height = 2.0f);
	~Character();

	void Update();
	void Render();
	void Debug();

	ModelAnimator* GetModel() { return model; }

private:
	ModelAnimator* model;
};
