#pragma once
class Onix
{
public:
	Onix();
	~Onix();

	void Update();
	void Render();
	void Move();
private:
	vector<ColliderSphere*> bodies;
	
	vector<Vector3> dests;
	vector<Vector3> sources;
	Vector3 deltaPos = Vector3(0, 0, 0);
	float moveCool = 1;
	float time = 0;
};

