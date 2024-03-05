#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
	sprite = new Sprite(L"Effect/greenCore_4x4.png", Vector2(30, 30), 4, 4, true);
	//sprite->Play(Vector3(0, 0, 0));

	collider = new ColliderSphere(50);
}

ParticleScene::~ParticleScene()
{
	delete sprite;
	delete collider;
}

void ParticleScene::Update()
{
	sprite->Update();
	collider->Update();
	if (KEY_DOWN(VK_LBUTTON))
	{
		Ray ray = CAMERA->ScreenPointToRay(mousePos);

		HitResult hitResult;

		if (collider->Collision(ray, &hitResult))
		{
			sprite->Play(hitResult.impactPoint);
		}
	}
}

void ParticleScene::PreRender()
{
}

void ParticleScene::Render()
{
	sprite->Render();
	collider->Render();
}

void ParticleScene::PostRender()
{
}
