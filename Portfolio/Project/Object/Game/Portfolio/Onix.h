#pragma once
class Onix
{
public:
	Onix();
	~Onix();

	void Update();
	void Render();
	void SpinMove();
	void Debug();
	void BodyMove();
	void Stay();
	void Input();
private:
	Transform* parent;
	vector<ColliderSphere*> bodies;
	ModelInstancing* texture;
	Model* head;
	//vector<Model*> bodiesTexture;
	vector<Vector3> dests;
	vector<Vector3> sources;
	Vector3 deltaPos = Vector3(0, 0, 0);
	float moveCool = 1;
	float time = 0;
	float distanceBetweenBody = 2.0f;
};

