#include "Framework.h"
#include "Target.h"
Target::Target()
{
	names.push_back(L"Black.png");
	names.push_back(L"Cyan.png");
	names.push_back(L"Green.png");
	names.push_back(L"White.png");
	names.push_back(L"Yellow.png");
}

Target::~Target()
{
	delete colliderBody;
}

void Target::Update()
{
	Transform::Update();
	lifeTime -= DELTA_TIME;
	if (lifeTime <= 0)
	{
		lifeTime = 0;
		isActive = false;
	}
}

void Target::Render()
{
}

void Target::Debug()
{
}

void Target::Respawn(float lifeTime, Vector3 pos)
{
	if (isActive)
	{
		return;
	}
	isActive = true;
	this->lifeTime = lifeTime;
	this->translation = pos;

}

