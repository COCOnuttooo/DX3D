#include "Framework.h"
#include "PortfolioScene.h"
PortfolioScene::PortfolioScene()
{
	onix = new Onix;
	target = new Sphere();
	player = new Knight();
	onix->SetTarget(player);
	target->translation = Vector3(10, 0, 10);
	terrain = new Terrain(L"HeightMap/HeightMap.png");
	plane = new Quad();
	plane->GetMaterial()->SetDiffuseMap(L"Landscape/Fieldstone_DM.tga");
	plane->scale *= 100;
	plane->Update();
	//plane->translation = Vector3(0.5 * plane->scale.x, 0, 0.5 * plane->scale.x);
	plane->rotation.x = XM_PIDIV2;
	player->translation.y = 2;
	player->translation.x = 20;
	player->Update();
	onix->Update();
	onix->Update();
	plane->Update();
	
}

PortfolioScene::~PortfolioScene()
{
	delete onix;
	delete terrain;
	delete plane;
	delete player;
	delete target;
}

void PortfolioScene::Update()
{
	if (KEY_DOWN(VK_SPACE))
	{
		isPlaying = true;
	}
	if (!isPlaying)
		return;
	onix->Update();
	target->Update();
	plane->Update();
	player->Update();
	for (auto& body : onix->GetBodies())
	{
		if (player->Collision(body))
		{
			player->GetHitP1();
		}

	}
	//if (KEY_PRESS('W'))
	//{
	//	target->translation += target->GetForwardVector() * 2 * DELTA_TIME;
	//}
	//if (KEY_PRESS('S'))
	//{
	//	target->translation -= target->GetForwardVector() * 2 * DELTA_TIME;
	//}
	//if (KEY_PRESS('A'))
	//{
	//	target->translation -= target->GetRightVector() * 2 * DELTA_TIME;

	//}
	//if (KEY_PRESS('D'))
	//{
	//	target->translation += target->GetRightVector() * 2 * DELTA_TIME;
	//}
	//terrain->Update();
}

void PortfolioScene::PreRender()
{
	
}

void PortfolioScene::Render()
{
	onix->Render();
	target->Render();
	plane->Render();
	player->Render();
	//terrain->Render();
}

void PortfolioScene::PostRender()
{
	player->Debug();
	onix->Debug();
	target->Debug();
	//terrain->GetMaterial()->Debug();
}
