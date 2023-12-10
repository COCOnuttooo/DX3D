#include "Framework.h"
#include "RobotScene.h"

RobotScene::RobotScene()
{
	bot = new HomeworkBot;
	//ENVIRONMENT->GetCamera()->SetParent(bot->GetCameraLookAt());
}

RobotScene::~RobotScene()
{
}

void RobotScene::Update()
{
	bot->Update();
}

void RobotScene::PreRender()
{
}

void RobotScene::Render()
{
	bot->Render();
}

void RobotScene::PostRender()
{
}
