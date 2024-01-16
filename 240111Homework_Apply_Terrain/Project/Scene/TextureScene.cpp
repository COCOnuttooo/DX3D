#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
	//quad = new Quad();
	//quad->GetMaterial()->SetDiffuseMap(L"Landscape/Box.png");
	cube = new TextureCube();
	earth = new Sphere;
	earth->GetMaterial()->SetDiffuseMap(L"Landscape/Fieldstone_DM.tga");
	earth->GetMaterial()->SetSpecularMap(L"Landscape/Fieldstone_SM.tga");
	earth->GetMaterial()->SetNormalMap(L"Landscape/Fieldstone_NM.tga");
	//earth->GetMaterial()->SetSpecularMap(L"SolarSystem/earthspec.jpg");
	sun = new Sphere;
	sun->GetMaterial()->SetDiffuseMap(L"SolarSystem/sunmap.jpg");
	earth->translation.x = 5;
	//earth->translation.x = 2;
}

TextureScene::~TextureScene()
{
	//delete quad;
	delete cube;
	delete earth;
	delete sun;
}

void TextureScene::Update()
{
	//quad->Update();
	cube->Update();
	earth->Update();
	//sun->Update();
}

void TextureScene::PreRender()
{
}

void TextureScene::Render()
{
	//quad->Render();
	cube->Render();
	earth->Render();
	//sun->Render();
}

void TextureScene::PostRender()
{
	//cube->Debug();
}
