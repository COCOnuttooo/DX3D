#include "Framework.h"
#include "GridScene.h"
GridScene::GridScene()
{
	grid = new Grid;
}

GridScene::~GridScene()
{
	delete grid;
}

void GridScene::Update()
{
	grid->Update();
}

void GridScene::PreRender()
{
	grid->Render(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

}

void GridScene::Render()
{
	grid->Render(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

void GridScene::PostRender()
{
}

void GridScene::P1ReRender()
{
}

void GridScene::P2ReRender()
{
}


