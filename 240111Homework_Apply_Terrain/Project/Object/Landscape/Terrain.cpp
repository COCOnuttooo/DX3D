#include "Framework.h"
#include "Terrain.h"


Terrain::Terrain(wstring heightMapFile)
	:GameObject(L"HomeworkTerrain")
{
	heightMap = Texture::Add(heightMapFile);

	CreateMesh();
}

Terrain::~Terrain()
{
}

float Terrain::GetHeight(Vector3 position)
{
	if (!heightMap) return 0.f;

	position = XMVector3TransformCoord(position, XMMatrixInverse(nullptr, world));

	int x = position.x;
	int z = position.z;

	if (x < 0 || x >= width - 1)
		return 0.f;
	if (z < 0 || z >= height - 1)
		return 0.f;

	UINT index[4];

	index[0] = (x + 0) + width * (z + 0);
	index[1] = (x + 1) + width * (z + 0);
	index[2] = (x + 0) + width * (z + 1);
	index[3] = (x + 1) + width * (z + 1);

	Vector3 vertex[4];

	for (UINT i = 0; i < 4; i++)
	{
		vertex[i] = vertices[index[i]].pos;
	}

	float u = abs(position.x - vertex[0].x);
	float v = abs(position.z - vertex[0].z);

	Vector3 result{};

	if (u + v <= 1.f)
	{
		// 0, 1, 2 사용
		result = vertex[0] + (vertex[2] - vertex[0]) * u + (vertex[1] - vertex[0]) * v;
	}
	else
	{
		// 1, 2, 3 사용
		result = vertex[3] + (vertex[2] - vertex[3]) * u + (vertex[1] - vertex[3]) * v;
	}

	return result.y;
}

void Terrain::LoadMaterial(wstring file)
{
	material->Load(file);
	material->SetShader(L"HomeworkTerrain");
}

void Terrain::Render(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	if (alphaMap)			
		alphaMap->PSSetShaderResources(10);
	if (secondDiffuseMap)	
		secondDiffuseMap->PSSetShaderResources(11);

	GameObject::Render(topology);
}

void Terrain::LoadAlphaMap(wstring file)
{
	//file = L"HeightMap/" + file;
	alphaMap = Texture::Add(file);
	//vector<Vector4> pixels = alphaMap->ReadPixels();

	//UINT size = min(pixels.size(), vertices.size());
	//for (UINT i = 0; i < size; i++)
	//{
	//	vertices[i].alpha.x = pixels[i].x;
	//	vertices[i].alpha.y = pixels[i].y;
	//	vertices[i].alpha.z = pixels[i].z;
	//	vertices[i].alpha.w = pixels[i].w;
	//}
	//mesh->UpdateVertex(vertices.data(), vertices.size());
}

void Terrain::LoadSecondDiffuseMap(wstring file)
{
	secondDiffuseMap = Texture::Add(file);
}




void Terrain::CreateMesh()
{
	vector<Vector4> colors{};

	if (heightMap)
	{
		colors = heightMap->ReadPixels();

		width = heightMap->GetSize().x;
		height = heightMap->GetSize().y;
	}

	for (UINT z = 0; z < height; z++)
	{
		for (UINT x = 0; x < width; x++)
		{
			VertexType vertex;

			vertex.pos = Vector3(x, 0, z);

			vertex.uv.x = (float)x / (width - 1);
			vertex.uv.y = 1.f - (float)z / (height - 1);

			UINT index = x + width * z;

			if (!colors.empty())
				vertex.pos.y = colors[index].x * HEIGHT_SCALE;

			vertices.emplace_back(vertex);
		}
	}

	for (UINT i = 0; i < height - 1; i++)
	{
		for (UINT j = 0; j < width - 1; j++)
		{
			indices.emplace_back((i + 0) * width + (j + 0));
			indices.emplace_back((i + 1) * width + (j + 0));
			indices.emplace_back((i + 0) * width + (j + 1));

			indices.emplace_back((i + 1) * width + (j + 0));
			indices.emplace_back((i + 1) * width + (j + 1));
			indices.emplace_back((i + 0) * width + (j + 1));
		}
	}

	// Create Normal Vector
	for (UINT i = 0; i < indices.size() / 3; i++) // 폴리곤의 개수만큼 normal 생성
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		Vector3 v01 = vertices[index1].pos - vertices[index0].pos;
		Vector3 v02 = vertices[index2].pos - vertices[index0].pos;

		Vector3 normal = Vector3::Cross(v01, v02).GetNormalized();

		// 추후 평균을 냄
		vertices[index0].normal += normal;
		vertices[index1].normal += normal;
		vertices[index2].normal += normal;
	}

	CalculateTangent();

	mesh = new Mesh(vertices, indices);
}

void Terrain::CalculateTangent()
{
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		Vector3 p0 = vertices[index0].pos;
		Vector3 p1 = vertices[index1].pos;
		Vector3 p2 = vertices[index2].pos;

		Vector2 uv0 = vertices[index0].uv;
		Vector2 uv1 = vertices[index1].uv;
		Vector2 uv2 = vertices[index2].uv;

		Vector3 e0 = p1 - p0;
		Vector3 e1 = p2 - p0;

		float u0 = uv1.x - uv0.x;
		float v0 = uv1.y - uv0.y;

		float u1 = uv2.x - uv0.x;
		float v1 = uv2.y - uv0.y;

		float D = 1.f / (u0 * v1 - v0 * u1);

		Vector3 tangent = D * (e0 * v1 - e1 * v0);

		vertices[index0].tangent += tangent;
		vertices[index1].tangent += tangent;
		vertices[index2].tangent += tangent;
	}

	// Tangent길이 보정
	for (VertexType& vertex : vertices)
	{
		Vector3 T = vertex.tangent;
		Vector3 N = vertex.normal;

		vertex.tangent = Vector3(T - N * Vector3::Dot(N, T)).GetNormalized();
	}
}

