#include "Framework.h"
#include "MainGame.h"
#include "Scene/TutorialScene.h"
#include "Scene/RobotScene.h"

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
    KEYBOARD->Update();
    TIME->Update();
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
    scene = new RobotScene;
    Device::GetInstance();
    Environment::GetInstance();
    //Create Vertex
}

void MainGame::Release()
{
         Device::Delete();
    Environment::Delete();
         Shader::Delete();
           Time::Delete();
       Keyboard::Delete();
         delete scene;
}
