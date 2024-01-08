#include "Framework.h"
#include "PortalQuad.h"

PortalQuad::PortalQuad(Vector2 size)
	:GameObject<VertexType>(L"01_Texture"), size(size)
{
	CreateMesh();
	cameraBox = new TextureCube;
	cameraBox->SetDiffuseMap(L"Landscape/Bricks.png");
	edge = new Quad(Vector2(this->size.x* 1.1, this->size.y * 1.1));
	edge->SetParent(this);
	//edge->rotation = Vector3(0, XM_PI, 0);
	edge->GetMaterial()->SetDiffuseMap(L"Landscape/Dirt.png");
	edge->translation.z = 0.01;
}

PortalQuad::~PortalQuad()
{
	delete cameraBox;
	delete edge;
}

void PortalQuad::Render()
{
	edge->Render();
	GameObject::Render();
	cameraBox->Render();
}

void PortalQuad::Update()
{
	GameObject::Update();
	cameraBox->Update();
	edge->Update();
}

void PortalQuad::SetCamera(Transform* parent)
{
	cameraBox->SetParent(parent);
}

void PortalQuad::SetCameraDiffuse(wstring file)
{
	cameraBox->SetDiffuseMap(file);
}

void PortalQuad::CreateMesh()
{
	float L = -size.x * 0.5f;
	float R = +size.x * 0.5f;
	float B = -size.y * 0.5f;
	float T = +size.y * 0.5f;
	float uvOffsetX = size.x / WIN_WIDTH;
	float uvOffsetY = size.y / WIN_WIDTH;
	//vertices.emplace_back(Vector3(L, T, 0.0f), Vector2(0, 0));
	//vertices.emplace_back(Vector3(R, T, 0.0f), Vector2(1, 0));
	//vertices.emplace_back(Vector3(L, B, 0.0f), Vector2(0, 1));
	//vertices.emplace_back(Vector3(R, B, 0.0f), Vector2(1, 1));

	//vertices =
	//{
	//	{Vector3(L, T, 0.0f), Vector2(0.5-uvOffsetX, 0.5+uvOffsetY)},
	//	{Vector3(R, T, 0.0f), Vector2(0.5+uvOffsetX, 0.5+uvOffsetY)},
	//	{Vector3(L, B, 0.0f), Vector2(0.5-uvOffsetX, 0.5-uvOffsetY)},
	//	{Vector3(R, B, 0.0f), Vector2(0.5+uvOffsetX, 0.5-uvOffsetY)}
	//};
	float scaleX = WIN_HEIGHT / WIN_WIDTH * 0.5f;
	vertices =
	{
		{Vector3(L, T, 0.0f), Vector2(0.5 - scaleX, 0)},
		{Vector3(R, T, 0.0f), Vector2(0.5 + scaleX, 0)},
		{Vector3(L, B, 0.0f), Vector2(0.5 - scaleX, 1)},
		{Vector3(R, B, 0.0f), Vector2(0.5 + scaleX, 1)}
	};
	indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	mesh = new Mesh(vertices, indices);
}
