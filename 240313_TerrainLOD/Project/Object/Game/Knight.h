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
	
	void Update();

	void SetClip(State state);

private:
	void Move();

private:
	float moveSpeed = 3.0f;
};
