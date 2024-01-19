#include "Framework.h"
#include "TextureCube.h"
TextureCube::TextureCube()
{
	CreateQuads();
	SetDiffuseMap(L"Landscape/Box.png");
}

TextureCube::~TextureCube()
{
	for (auto& i : quads)
		delete i;
}

void TextureCube::Update()
{
	Transform::Update();
	for (auto& i : quads)
		i->Update();
}

void TextureCube::Render()
{
	for (auto& i : quads)
		i->Render();
}

void TextureCube::SetDiffuseMap(wstring file)
{
	for (auto& i : quads)
		i->GetMaterial()->SetDiffuseMap(file);
}

void TextureCube::CreateQuads()
{
	//STL : resize, reserve
	quads.resize(6);

	quads[FRONT] = new Quad();
	quads[FRONT]->SetParent(this);
	quads[FRONT]->translation.z = -0.5f;

	quads[BACK] = new Quad();
	quads[BACK]->SetParent(this);
	quads[BACK]->translation.z = 0.5f;
	quads[BACK]->rotation.x = XM_PI;

	quads[LEFT] = new Quad();
	quads[LEFT]->SetParent(this);
	quads[LEFT]->translation.x = -0.5f;
	quads[LEFT]->rotation.y = XM_PIDIV2;

	quads[RIGHT] = new Quad();
	quads[RIGHT]->SetParent(this);
	quads[RIGHT]->translation.x = +0.5f;
	quads[RIGHT]->rotation.y = -XM_PIDIV2;

	quads[BOTTOM] = new Quad();
	quads[BOTTOM]->SetParent(this);
	quads[BOTTOM]->translation.y = -0.5f;
	quads[BOTTOM]->rotation.x = -XM_PIDIV2;

	quads[TOP]= new Quad();
	quads[TOP]->SetParent(this);
	quads[TOP]->translation.y = 0.5f;
	quads[TOP]->rotation.x = XM_PIDIV2;
}
