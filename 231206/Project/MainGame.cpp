#include "Framework.h"
#include "MainGame.h"

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

	



}

void MainGame::Render()
{
    ENVIRONMENT->Set();
    cube->Render();
    /////////////////////////////////////


}

void MainGame::PreRender()
{
}

void MainGame::PostRender()
{
}

void MainGame::Initialize()
{
    Device::GetInstance();
    Environment::GetInstance();
    cube = new Cube;
    //Create Vertex
  





}

void MainGame::Release()
{
         Device::Delete();
    Environment::Delete();
         Shader::Delete();
    delete cube;

}
