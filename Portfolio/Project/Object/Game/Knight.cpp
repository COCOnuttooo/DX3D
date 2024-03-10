#include "Framework.h"
#include "Knight.h"

Knight::Knight()
	:Character("Knight")
{
	GetModel()->ReadClip("Happy Idle");
	GetModel()->ReadClip("Fast Run");
	GetModel()->ReadClip("Hip Hop Dancing");
	GetModel()->ReadClip("Sweep Fall");
	GetModel()->ReadClip("Getting Up");
	CAMERA->SetTarget(this);
	GetModel()->GetClip(FALLDOWN)->AddEvent(0.8f, bind(&Knight::SetClip, this, GETTINGUP));
	 GetModel()->GetClip(DANCING)->AddEvent(0.8f, bind(&Knight::SetClip, this, IDLE));
	 GetModel()->GetClip(GETTINGUP)->AddEvent(0.8f, bind(&Knight::SetClip, this, IDLE));
	 GetModel()->GetClip(GETTINGUP)->AddEvent(0.7f, bind(&Knight::SetActive, this));
}

Knight::~Knight()
{
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

	if (KEY_PRESS('A'))
	{
		rotation.y -= DELTA_TIME;
	}

	if (KEY_PRESS('D'))
	{
		rotation.y += DELTA_TIME;
	}
	if (KEY_UP('W')|| KEY_UP('S'))
		SetClip(IDLE);

	if (KEY_DOWN(VK_LBUTTON))
	{
		SetClip(DANCING);
	}
}

void Knight::Update()
{
	__super::Update();
	//SetActive();
	if (curState != GETTINGUP && curState != FALLDOWN)
	{

		Move();
	}
}

void Knight::SetClip(State state)
{
	if (curState != state)
	{
		model->PlayClip(state);

		curState = state;
	}
}

void Knight::GetHitP1()
{
	if (!isActive)
	{
		return;
	}
	isActive = false;
	invincibleCool = 3.0f;
	model->PlayClip(FALLDOWN);
}

void Knight::SetActive()
{
	isActive = true;
	//invincibleCool -= DELTA_TIME;
	//if (invincibleCool <= 0)
	//{
	//	invincibleCool = 0;
	//}
}
