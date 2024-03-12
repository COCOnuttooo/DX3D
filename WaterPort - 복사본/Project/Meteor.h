#pragma once
class Meteor
{
public:
	Meteor();
	~Meteor();
	void Update();
	void Render();
	void Debug();
private:
	Collider* collider;
	Model* model;
	MeteorEffect* effect;
};

