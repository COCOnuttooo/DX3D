#include "Framework.h"
#include "SkyBox.h"


SkyBox::SkyBox(wstring file)
{
	sphere = new Sphere;
	sphere->GetMaterial()->SetShader(L"15_SkyBox");
	sphere->SetName("SkyBox");

	cubeMap = Texture::Add(file);
	//sphere->SetParent(CAMERA);
}

SkyBox::~SkyBox()
{
	delete sphere;
}

void SkyBox::Render()
{
	cubeMap->PSSetShaderResources(10);
	STATE->SetFrontCounterClockWise();
	STATE->DisableDepth();

	sphere->Render();
	STATE->SetFrontClockWise();
	STATE->EnableDepth();
}

void SkyBox::Update()
{
	sphere->Update();
}