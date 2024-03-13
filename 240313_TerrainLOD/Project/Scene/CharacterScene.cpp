#include "Framework.h"
#include "CharacterScene.h"

CharacterScene::CharacterScene()
{
	player = new Knight;
}

CharacterScene::~CharacterScene()
{
	delete player;
}

void CharacterScene::Update()
{
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
