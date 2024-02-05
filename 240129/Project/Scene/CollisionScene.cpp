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
	for (UINT i = 0; i < 2; i++)
	{
		Collider* collider = new ColliderCapsule();
		collider->translation = { i * 2.0f ,10, 0 };
		collider->SetName("ColliderCapsule" + to_string(i));
		colliders.push_back(collider);

	}
	//colliders.push_back(new ColliderSphere);
	//colliders.push_back(new ColliderSphere);
	//colliders.push_back(new ColliderBox);
	//colliders.push_back(new ColliderBox);
	crossHair = new Quad;
	crossHair->GetMaterial()->SetDiffuseMap(L"UI/CrossHair.png");
	crossHair->GetMaterial()->SetShader(L"01_Texture");
	crossHair->translation = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f, 0.0f };
	crossHair->scale = { 100,100,1 };
}

CollisionScene::~CollisionScene()
{
	for (Collider* collider : colliders)
	{
		delete collider;
	}
	delete crossHair;
}

void CollisionScene::Update()
{
	static HitResult hitResult;
	Ray ray = CAMERA->ScreenPointToRay(mousePos);
	if (colliders[4]->Collision(ray, &hitResult))
		colliders[4]->SetColor(1, 0, 0);
	else
		colliders[4]->SetColor(0, 1, 0);
	//if (KEY_DOWN(VK_LBUTTON))
	//{

	//	colliders[0]->translation = hitResult.imapactPoint;
	//}
	//if (colliders[0]->Collision(colliders[2]))
	//{
	//	colliders[0]->SetColor(1, 0, 0);
	//	colliders[1]->SetColor(1, 0, 0);
	//}
	//else
	//{
	//	colliders[0]->SetColor(0, 1, 0);
	//	colliders[1]->SetColor(0, 1, 0);

	//}

	if (colliders[4]->Collision(colliders[5]))
	{
		colliders[4]->SetColor(1, 0, 0);
		colliders[5]->SetColor(1, 0, 0);
	}
	else
	{
		colliders[4]->SetColor(0, 1, 0);
		colliders[5]->SetColor(0, 1, 0);

	}
	//if (colliders[0]->Collision(ray, &hitResult))
	//{
	//	colliders[0]->SetColor(1, 0, 0);
	//}
	//else
	//	colliders[0]->SetColor(0, 1, 0);

	for (Collider* collider : colliders)
	{
		collider->Update();
	}
	crossHair->translation = {mousePos.x , WIN_HEIGHT - mousePos.y , 0};
	crossHair->Update();

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
	ENVIRONMENT->PostSet();
	crossHair->Render();
	crossHair->Debug();
}

