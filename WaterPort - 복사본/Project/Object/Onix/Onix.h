#pragma once
class Onix
{
	enum OnixStates
	{
		ONIXIDLE,
		PATTERN1,
		PATTERN2,
		PATTERN3,
		PATTERN4,
		PATTERN5,
	};
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
	void SetDirection(Vector3 dest);
	void SetTarget(Transform* target) { this->target = target; };

	void Pattern1();
	void Pattern2();
	vector<ColliderSphere*> GetBodies() { return bodies; }
private:
	OnixStates state = ONIXIDLE;
	Transform* target;
	Vector3 dest;
	Transform* parent;
	vector<ColliderSphere*> bodies;
	ModelInstancing* texture;
	Model* head;
	//vector<Model*> bodiesTexture;
	vector<Vector3> dests;
	vector<Vector3> sources;
	Vector3 deltaPos = Vector3(0, 0, 0);
	float moveSpeed = 3.0f;
	float moveCool = 1;
	float time = 0;
	float distanceBetweenBody = 2.0f;
	WindEffect* windEffect;
};

