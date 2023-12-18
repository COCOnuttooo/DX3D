#include "Framework.h"
#include "BoxScene.h"

BoxScene::BoxScene()
{
	//quad = new Quad;
	//quad->GetMaterial()->SetDiffuseMap(L"Landscape/Box.png");
	box = new BoxCube;
	ray = new Cube;
	ray->SetParent(ENVIRONMENT->GetMainCamera());
	ray->translation.z = 10;
	ray->scale.z = 10;
	ray->scale.x = 0.2;
	ray->scale.y = 0.2;
}

BoxScene::~BoxScene()
{
	//delete quad;
	delete box;
	delete ray;
}

void BoxScene::Update()
{
	box->Update();
	ray->Update();
}

void BoxScene::PreRender()
{

}

void BoxScene::Render()
{
	box->Render();
}

void BoxScene::PostRender()
{
	box->Debug();
	ray->Render();

}
