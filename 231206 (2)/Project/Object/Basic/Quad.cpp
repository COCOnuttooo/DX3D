#include "Framework.h"
#include "Quad.h"

Quad::Quad(Vector2 size)
	:GameObject<VertexType>(L"03_DiffuseTexture"), size(size)
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
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		Vector3 v01 = vertices[index1].pos - vertices[index0].pos;
		Vector3 v02 = vertices[index2].pos - vertices[index0].pos;

		Vector3 normal = Vector3::Cross(v01, v02);

		vertices[index0].normal += normal;
		vertices[index1].normal += normal;
		vertices[index2].normal += normal;
	}

	mesh = new Mesh(vertices, indices);
}
