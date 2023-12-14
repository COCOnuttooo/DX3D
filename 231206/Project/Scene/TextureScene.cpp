#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	quad = new Quad();
	quad->GetMaterial()->SetDiffuseMap(L"Landscape/Box.png");
}

TextureScene::~TextureScene()
{
	delete quad;
}

void TextureScene::Update()
{
	quad->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	quad->Render();
}

void TextureScene::PostRender()
{
}
