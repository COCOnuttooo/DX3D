#include "Framework.h"
#include "CharacterScene.h"

CharacterScene::CharacterScene()
{
	player = new Character("Knight");
	player->GetModel()->ReadClip("Happy Idle");
}

CharacterScene::~CharacterScene()
{
	delete player;
}

void CharacterScene::Update()
{
	if (KEY_PRESS('W'))
	{
		player->translation += player->GetForwardVector() * 10.0f * DELTA_TIME;
	}

	if (KEY_PRESS('S'))
	{
		player->translation -= player->GetForwardVector() * 10.0f * DELTA_TIME;
	}

	if (KEY_PRESS('A'))
	{
		player->rotation.y -= DELTA_TIME;
	}

	if (KEY_PRESS('D'))
	{
		player->rotation.y += DELTA_TIME;
	}
	player->Update();
}

void CharacterScene::PreRender()
{
	
}

void CharacterScene::Render()
{
	player->Render();
}

void CharacterScene::PostRender()
{
	player->Debug();
}

