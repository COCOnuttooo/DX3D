#pragma once
class Target : public Transform
{
public:
	Target();
	~Target();
	virtual void Update();
	virtual void Render();
	virtual void Debug();
	virtual void Respawn(float lifeTime, Vector3 pos);
	bool GetIsActive() { return isActive; }
	float GetScore() { return score; }
	void AddEvent(function<void(float)> Event) { this->Event = Event; };

protected:
	function<void(float)> Event = nullptr;

	float baseScore = 100;
	float score = 0;
	bool isActive = false;
	float lifeTime = 0.0f;
	Collider* colliderBody = nullptr;
	vector<wstring> names;

};
