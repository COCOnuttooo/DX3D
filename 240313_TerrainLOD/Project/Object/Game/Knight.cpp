#include "Framework.h"
#include "Knight.h"

Knight::Knight()
	:Character("Knight")
{
	GetModel()->ReadClip("Happy Idle");
	GetModel()->ReadClip("Fast Run");
	GetModel()->ReadClip("Hip Hop Dancing");

	CAMERA->SetTarget(this);

	GetModel()->GetClip(DANCING)->AddEvent(0.9f, bind(&Knight::SetClip, this, IDLE));
}

Knight::~Knight()
{
}

void Knight::Update()
{
	__super::Update();

	Move();
}

void Knight::SetClip(State state)
{
	if (curState != state)
	{
		GetModel()->PlayClip(state);

		curState = state;
	}
}

void Knight::Move()
{
	if (KEY_PRESS('W'))
	{
		translation += GetForwardVector() * moveSpeed * DELTA_TIME;
		
		SetClip(RUN);
	}

	if (KEY_PRESS('S'))
	{
		translation -= GetForwardVector() * moveSpeed * DELTA_TIME;

		SetClip(RUN);
	}

	if (KEY_UP('W') || KEY_UP('S'))
		SetClip(IDLE);

	if (KEY_PRESS('A'))
	{
		rotation.y -= DELTA_TIME;
	}

	if (KEY_PRESS('D'))
	{
		rotation.y += DELTA_TIME;
	}

	if (KEY_DOWN(VK_LBUTTON))
		SetClip(DANCING);
}
