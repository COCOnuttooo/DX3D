#include "Framework.h"
#include "PortfolioScene.h"
PortfolioScene::PortfolioScene()
{
	onix = new Onix;
}

PortfolioScene::~PortfolioScene()
{
	delete onix;
}

void PortfolioScene::Update()
{
	onix->Update();
}

void PortfolioScene::PreRender()
{
	
}

void PortfolioScene::Render()
{
	onix->Render();
}

void PortfolioScene::PostRender()
{
}
