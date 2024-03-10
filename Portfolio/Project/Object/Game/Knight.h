#pragma once
class Knight : public Character
{
	enum State
	{
		IDLE, RUN, DANCING, FALLDOWN, GETTINGUP
	} curState = IDLE; 
public:
	Knight();
	~Knight();
	void Move();
	void Update();
	void SetClip(State state);
	void GetHitP1();
	void SetActive();
private:
	float invincibleCool = 0.0f;
	float moveSpeed = 9.0f;
};
