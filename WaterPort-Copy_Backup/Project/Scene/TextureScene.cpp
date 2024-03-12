#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	quad = new Quad;
	quad->GetMaterial()->SetDiffuseMap(L"Landscape/Box.png");

	cube = new TextureCube();
	cube->SetDiffuseMap(L"Landscape/Box.png");
	cube->SetName("TextureCube");
	cube->translation.x = -2;

	sphere = new Sphere();
	sphere->GetMaterial()->SetDiffuseMap(L"Landscape/FieldStone_DM.tga");
	sphere->GetMaterial()->SetSpecularMap(L"Landscape/FieldStone_SM.tga");
	sphere->GetMaterial()->SetNormalMap(L"Landscape/FieldStone_NM.tga");
}

TextureScene::~TextureScene()
{
	delete quad;
	
	delete cube;

	delete sphere;
}

void TextureScene::Update()
{
	  quad->Update();
	  cube->Update();
	sphere->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	  quad->Render();
	  cube->Render();
	sphere->Render();
}

void TextureScene::PostRender()
{
	cube->Debug();
}
