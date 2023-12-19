#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	quad = new Quad();
	quad->GetMaterial()->SetDiffuseMap(L"Landscape/Box.png");
	cube = new TextureCube();
}

TextureScene::~TextureScene()
{
	delete quad;
}

void TextureScene::Update()
{
	quad->Update();
	cube->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	quad->Render();
	cube->Render();
}

void TextureScene::PostRender()
{
	cube->Debug();
}
