#include "Framework.h"
#include "CollisionScene.h"
CollisionScene::CollisionScene()
{
	for (UINT i = 0; i < 2; i++)
	{
		Collider* collider = new ColliderBox();
		collider->translation = { i * 2.0f ,0, 0 };
		collider->SetName("ColliderBox" + to_string(i));
		colliders.push_back(collider);
	}
	for (UINT i = 0; i < 2; i++)
	{
		Collider* collider = new ColliderSphere();
		collider->translation = { i * 2.0f ,2, 0 };
		collider->SetName("ColliderSphere" + to_string(i));
		colliders.push_back(collider);

	}
	//colliders.push_back(new ColliderSphere);
	//colliders.push_back(new ColliderSphere);
	//colliders.push_back(new ColliderBox);
	//colliders.push_back(new ColliderBox);
	
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
	static HitResult hitResult;
	Ray ray = CAMERA->ScreenPointToRay(mousePos);
	if (colliders[2]->Collision(ray, &hitResult))
		colliders[2]->SetColor(1, 0, 0);
	else
		colliders[2]->SetColor(0, 1, 0);
	//if (KEY_DOWN(VK_LBUTTON))
	//{

	//	colliders[0]->translation = hitResult.imapactPoint;
	//}
	if (colliders[0]->Collision((ColliderBox*)colliders[1]))
	{
		colliders[0]->SetColor(1, 0, 0);
		colliders[1]->SetColor(1, 0, 0);
	}
	else
	{
		colliders[0]->SetColor(0, 1, 0);
		colliders[1]->SetColor(0, 1, 0);

	}
	for (Collider* collider : colliders)
	{
		collider->Update();
	}


	//if (colliders[2]->Collision((ColliderSphere*)colliders[3]))
	//{
	//	colliders[2]->SetColor(1, 0, 0);
	//	colliders[3]->SetColor(1, 0, 0);
	//}
	//else
	//{
	//	colliders[2]->SetColor(0, 1, 0);
	//	colliders[3]->SetColor(0, 1, 0);
	//}


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

		collider->Debug();
	}
}

