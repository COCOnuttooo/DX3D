#include "Framework.h"
#include "MeteorEffect.h"
MeteorEffect::MeteorEffect(Transform* target)
{
	particle =  new ComputingEffect(L"Effect/Snow.png", target, 1, 150, Vector3(166 / 255.0f, 106 / 255.f, 10 / 255.f) ,    0.7);
	particle2 = new ComputingEffect(L"Effect/Snow.png", target, 1, 300, Vector3(114 / 255.0f, 25 / 255.f, 25 / 255.f) ,    0.9);
	particle3 = new ComputingEffect(L"Effect/Snow.png", target, 1.2, 200, Vector3(100 / 255.f, 100 / 255.f, 100 / 255.f) , 0.9);
	particle4 = new ComputingEffect(L"Effect/Snow.png", target, 2, 50, Vector3(0.f, 0.f, 0.f)                            , 0.7);
}

MeteorEffect::~MeteorEffect()
{
	delete particle;
	delete particle2;
	delete particle3;
	delete particle4;
}

void MeteorEffect::Update()
{
	particle-> Update();
	particle2->Update();
	particle3->Update();
	particle4->Update();
}

void MeteorEffect::Render()
{
	 particle->Render();
	particle2->Render();
	particle3->Render();
	particle4->Render();
}

void MeteorEffect::Play()
{
	isActive = true;
	particle->Play(Vector3(0, 0, 0));
	particle2->Play(Vector3(0, 0, 0));
	particle3->Play(Vector3(0, 0, 0));
	particle4->Play(Vector3(0, 0, 0));
}

void MeteorEffect::Stop()
{
	isActive = false;
	particle ->Stop();
	particle2->Stop();
	particle3->Stop();
	particle4->Stop();
}

