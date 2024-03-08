#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
	particle = new Snow(L"Effect/Snow.png");
	//particle = new Sprite(L"Effect/greenCore_4x4.png", Vector2(50, 50), 4, 4, true);
	particle->Play(Vector3(0,0,0));
	//particle->Play(Vector3(0, 0, 0));

	collider = new ColliderSphere(50);
}

ParticleScene::~ParticleScene()
{
	delete particle;
	delete collider;
}

void ParticleScene::Update()
{
	particle->Update();
	collider->Update();
	if (KEY_DOWN(VK_LBUTTON))
	{
		Ray ray = CAMERA->ScreenPointToRay(mousePos);

		HitResult hitResult;

		if (collider->Collision(ray, &hitResult))
		{
			particle->Play(hitResult.impactPoint);
		}
	}
}


void ParticleScene::PreRender()
{
}

void ParticleScene::Render()
{
	particle->Render();
	collider->Render();
}

void ParticleScene::PostRender()
{
	particle->Debug();
}
