#include "Framework.h"
#include "ParticleScene.h"

ParticleScene::ParticleScene()
{
	target = new ColliderSphere();
	
	meteorEffect = new MeteorEffect(target);
	meteorEffect->Play();
	//particle = new Snow(L"Effect/Snow.png");
	//particle = new Sprite(L"Effect/greenCore_4x4.png", Vector2(50, 50), 4, 4, true);

	//particle->Play(Vector3(0, 0, 0));

	collider = new ColliderSphere(50);
	collider->scale *= 3;
	rock = new Model("Rock");
	rock->rotation.y = XM_PI;
	//rock->rotation.y = XM_PI;
	//rock->scale *= 0.1;
	//rock->translation.y = 0.5;
	rock->SetParent(target);
	onix = new Onix;
	onix->SetTarget(target);
	//particle->Stop();
}

ParticleScene::~ParticleScene()
{
	delete rock;
	delete meteorEffect;
	delete collider;
	delete target;
	delete onix;
}

void ParticleScene::Update()
{
	if (KEY_DOWN(VK_SPACE))
	{
		isPlay = true;
	}
	if (!isPlay)
	{
		return;
	}

	meteorEffect->Update();
	collider->Update();
	target->translation += target->GetForwardVector() * DELTA_TIME * 5;
	target->Update();
	rock->Update();
	onix->Update();



}


void ParticleScene::PreRender()
{
}

void ParticleScene::Render()
{
	//collider->Render();
	//target->Render();
	rock->Render();
	meteorEffect->Render();
	onix->Render();
}

void ParticleScene::PostRender()
{
	target->Debug();
	rock->Debug();
}
