#include "Framework.h"
#include "Character.h"
Character::Character(string name, float radius, float height)
	:ColliderCapsule(radius, height)
{
	
	ColliderCapsule::SetName(name + "_Collider");
	ColliderCapsule::Load();
	//ColliderCapsule::SetParent(this);

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
