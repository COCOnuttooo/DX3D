#include "Framework.h"
#include "Quad.h"

Quad::Quad(Vector2 size)
	:GameObject<VertexType>(L"01_Texture"), size(size)
{
	CreateMesh();

	
}

Quad::~Quad()
{
}

void Quad::Render()
{
	GameObject::Render();
}

void Quad::Debug()
{
	//if (ImGui::TreeNode("QuadOption"))
	//{
	//	ImGui::Text("Pos : %d, %d, %d", (int)translation.x, (int)translation.y, (int)translation.z);
	//	ImGui::Text("Rot : %.2f, %.2f, %.2f", rotation.x, rotation.y, rotation.z);
	//	ImGui::SliderFloat("Rotation X", &rotation.x, 0, 2 * XM_PI);
	//	ImGui::SliderFloat("Rotation Y", &rotation.y, 0, 2 * XM_PI);
	//	ImGui::SliderFloat("Rotation Z", &rotation.z, 0, 2 * XM_PI);

	//	ImGui::SliderFloat("Scalee X", &scale.x, 0, 50);
	//	ImGui::SliderFloat("Scalee Y", &scale.y, 0, 50);
	//	ImGui::SliderFloat("Scalee Z", &scale.z, 0, 50);
	//	//ImGui::SliderFloat("Move Speed", &moveSpeed, 1.0f, 50.0f);
	//	//ImGui::SliderFloat("Rotate Speed", &rotateSpeed, 1.0f, 50.0f);
	//	if (ImGui::Button("Set Default"))
	//	{
	//		scale = { 1,1,1 };
	//		rotation = { 0,0,0 };
	//		translation = { 0,0,0 };

	//	}
	//	ImGui::TreePop();
	//}
}

void Quad::CreateMesh()
{
	float L = -size.x * 0.5f;
	float R = +size.x * 0.5f;
	float B = -size.y * 0.5f;
	float T = +size.y * 0.5f;

	//vertices.emplace_back(Vector3(L, T, 0.0f), Vector2(0, 0));
	//vertices.emplace_back(Vector3(R, T, 0.0f), Vector2(1, 0));
	//vertices.emplace_back(Vector3(L, B, 0.0f), Vector2(0, 1));
	//vertices.emplace_back(Vector3(R, B, 0.0f), Vector2(1, 1));

	vertices =
	{
		{Vector3(L, T, 0.0f), Vector2(0, 0)},
		{Vector3(R, T, 0.0f), Vector2(1, 0)},
		{Vector3(L, B, 0.0f), Vector2(0, 1)},
		{Vector3(R, B, 0.0f), Vector2(1, 1)}
	};

	indices =
	{
		0, 1, 2,
		2, 1, 3
	};

	mesh = new Mesh(vertices, indices);
}
