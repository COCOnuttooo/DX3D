#include "Framework.h"
#include "CollisionScene.h"
CollisionScene::CollisionScene()
{
	colliders.push_back(new ColliderSphere);
	colliders.push_back(new ColliderBox);
	
}

CollisionScene::~CollisionScene()
{
	for (Collider* collider : colliders)
	{
		delete collider;
	}
}

void CollisionScene::Update()
{
	for (Collider* collider : colliders)
	{
		collider->Update();
	}
}

void CollisionScene::PreRender()
{
}

void CollisionScene::Render()
{
	for (Collider* collider : colliders)
	{

		collider->Render();
	}
}

void CollisionScene::PostRender()
{
	for (Collider* collider : colliders)
	{

		collider->GetMaterial()->Debug();
	}
}

