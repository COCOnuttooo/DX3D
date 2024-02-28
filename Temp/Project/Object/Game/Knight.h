#pragma once
class Knight : public Character
{
	enum State
	{
		IDLE, RUN, DANCING
	} curState = IDLE; 
public:
	Knight();
	~Knight();
	void Move();
	void Update();
	void SetClip(State state);
private:
	float moveSpeed = 3.0f;
};
