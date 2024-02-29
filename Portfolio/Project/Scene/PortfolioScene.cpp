#include "Framework.h"
#include "PortfolioScene.h"
PortfolioScene::PortfolioScene()
{
	onix = new Onix;
	//terrain = new Terrain(L"HeightMap/HeightMap.png");
}

PortfolioScene::~PortfolioScene()
{
	delete onix;
	//delete terrain;
}

void PortfolioScene::Update()
{
	onix->Update();
	//terrain->Update();
}

void PortfolioScene::PreRender()
{
	
}

void PortfolioScene::Render()
{
	onix->Render();
	//terrain->Render();
}

void PortfolioScene::PostRender()
{
	onix->Debug();
	//terrain->GetMaterial()->Debug();
}
