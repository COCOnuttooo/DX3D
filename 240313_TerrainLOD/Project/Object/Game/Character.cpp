#include "Framework.h"
#include "Character.h"

Character::Character(string name, float radius, float height)
	:ColliderCapsule(radius, height)
{
	ColliderCapsule::SetName(name + "_Collider");
	ColliderCapsule::Load();

	model = new ModelAnimator(name);
	model->SetParent(this);

	Transform::Load();
}

Character::~Character()
{
	delete model;
}

void Character::Update()
{
	//ModelAnimator::Update();
	//Super::Update();

	 __super::Update();
	   model->Update();
}

void Character::Render()
{
	 __super::Render();
	   model->Render();
}

void Character::Debug()
{
	 __super::Debug();
	   model->Debug();
}
