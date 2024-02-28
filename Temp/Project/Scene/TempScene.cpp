#include "Framework.h"
#include "TempScene.h"
TempScene::TempScene()
{
	for (int i = 0; i < 10; i++)
	{

		Robot* bot = new Robot;
		bot->GetCollider()->translation = Vector3(i * 10, 2, i * 10);
		robots.push_back(bot);
	}
}

TempScene::~TempScene()
{
	for (auto& bot : robots)
	{
		delete bot;
	}
}

void TempScene::Update()
{
	for (auto& bot : robots)
	{
		bot->Update();;

	}
	if (c)
	{
		collider.rotation.y += XM_PI;
	if (collider.translation.x > 128)
		collider.translation.x = 127;

	if (collider.translation.x < -128)
		collider.translation.x = -127;

	if (collider.translation.z > 128)
		collider.translation.z = 127;

	if (collider.translation.z < -128)
		collider.translation.z = -127;
	}
}

void TempScene::PreRender()
{
}

void TempScene::Render()
{
	for (auto& bot : robots)
	{
		bot->Render();
	}
}

void TempScene::PostRender()
{
}
