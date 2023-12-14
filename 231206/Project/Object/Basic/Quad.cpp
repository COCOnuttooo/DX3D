#include "Framework.h"
#include "Quad.h"

Quad::Quad(Vector2 size)
	:GameObject<VertexType>(L"01_Texture"), size(size)
{
	CreateMesh();

	D3D11_SAMPLER_DESC desc = {};

	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.MipLODBias = 0;
	desc.MaxAnisotropy = 0;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MinLOD = 0;
	desc.MaxLOD = D3D11_FLOAT32_MAX;

	DEVICE->CreateSamplerState(&desc, &samplerState);

	DC->PSSetSamplers(0, 1, &samplerState);
}

Quad::~Quad()
{
	samplerState->Release();
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

	mesh = new Mesh(vertices, indices);
}
