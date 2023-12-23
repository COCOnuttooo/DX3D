#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	quad = new Quad();
	quad->GetMaterial()->SetDiffuseMap(L"Landscape/Box.png");
	cube = new TextureCube();
	cube2 = new TextureCube;
	cube2->SetParent(cube);
	cube2->translation.x = 20;
}

TextureScene::~TextureScene()
{
	delete quad;
	delete cube;
	delete cube2;
}

void TextureScene::Update()
{
	cube2->rotation.y += DELTA_TIME * 5;
	quad->Update();
	cube->Update();
	cube2->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	quad->Render();
	cube->Render();
	cube2->Render();
}

void TextureScene::PostRender()
{
	cube->Debug();
}

