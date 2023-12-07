#include "Framework.h"
#include "MainGame.h"
#include "Scene/TutorialScene.h"

MainGame::MainGame()
{
	Initialize();
}

MainGame::~MainGame()
{
	Release();
}

void MainGame::Update()
{
    ENVIRONMENT->Update();

    scene->Update();
}

void MainGame::Render()
{
    ENVIRONMENT->Set();
    /////////////////////////////////////
    scene->Render();
}

void MainGame::PreRender()
{
    scene->PreRender();
}

void MainGame::PostRender()
{
    scene->PostRender();
}

void MainGame::Initialize()
{
    scene = new TutorialScene;
    Device::GetInstance();
    Environment::GetInstance();
    //Create Vertex
}

void MainGame::Release()
{
         Device::Delete();
    Environment::Delete();
         Shader::Delete();
         delete scene;
}
