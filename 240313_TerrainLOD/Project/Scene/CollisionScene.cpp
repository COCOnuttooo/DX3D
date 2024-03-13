#include "Framework.h"
#include "CollisionScene.h"

CollisionScene::CollisionScene()
{
	for (UINT i = 0; i < 2; i++)
	{
		Collider* collider = new ColliderBox();
		collider->translation = { i * 2.0f, 0, 0 };
		collider->SetName("ColliderBox " + to_string(i));
		colliders.push_back(collider);
	}

	for (UINT i = 0; i < 2; i++)
	{
		Collider* collider = new ColliderSphere();
		collider->translation = { i * 2.0f, 2, 0 };
		collider->SetName("ColliderSphere " + to_string(i));
		colliders.push_back(collider);
	}

	for (UINT i = 0; i < 2; i++)
	{
		Collider* collider = new ColliderCapsule();
		collider->translation = { i * 2.0f, 6, 0 };
		collider->SetName("ColliderCapsule " + to_string(i));
		colliders.push_back(collider);
	}

	crossHair = new Quad();
	crossHair->GetMaterial()->SetDiffuseMap(L"UI/CrossHair.png");
	crossHair->GetMaterial()->SetShader(L"01_Texture");
	//crossHair->translation = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f, 0.0f };
	crossHair->scale = { 100, 100, 1 };
	
	hpBar = new ProgressBar(L"UI/hp_bar.png", L"UI/hp_bar_BG.png");
	hpBar->translation = { WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.1, 0 };

	hpBar->scale = { 300, 50, 1 };
}


CollisionScene::~CollisionScene()
{
	for (Collider* collider : colliders)
		delete collider;

	delete crossHair;

	delete hpBar;
}

void CollisionScene::Update()
{
	static HitResult hitResult;

	Ray ray = CAMERA->ScreenPointToRay(mousePos);

	//if (colliders[2]->Collision(ray, &hitResult))
	if (colliders[4]->Collision(colliders[5]))
		colliders[4]->SetColor(1, 0, 0);
	else
		colliders[4]->SetColor(0, 1, 0);

	//if (KEY_DOWN(VK_LBUTTON))
	//	colliders[0]->translation = hitResult.impactPoint;

	for (Collider* collider : colliders)
		collider->Update();

	crossHair->Update();

	crossHair->translation = mousePos;

	hpBar->Update();

	Vector3 pos = colliders[5]->GetGlobalPosition();

	pos.y += 2.0f;

	hpBar->translation = CAMERA->WorldToScreenPos(pos);
}

void CollisionScene::PreRender()
{
}

void CollisionScene::Render()
{
	for (Collider* collider : colliders)
		collider->Render();

}

void CollisionScene::PostRender()
{
	for (Collider* collider : colliders)
		collider->Debug();

	crossHair->Debug();

	ENVIRONMENT->PostSet();

	STATE->EnableAlpha();
	STATE->DisableDepth();

	    hpBar->Render();
	crossHair->Render();

	STATE->EnableDepth();


	static float value = 1.0f;

	ImGui::SliderFloat("Value", &value, 0.0f, 1.0f);

	hpBar->SetValue(value);
}
