#include "Framework.h"
#include "Terrain.h"
Terrain::Terrain(wstring heightMapFile)
	:GameObject(L"Test")
{
	heightMap = Texture::Add(heightMapFile);
	CreateMesh();
}

Terrain::~Terrain()
{
}

float Terrain::GetHeight(Vector3 position)
{
	//position -= translation;
	//position.x /= scale.x;
	//position.z /= scale.z;
	position = XMVector3TransformCoord(position, XMMatrixInverse(nullptr, world));


	int x = position.x;
	int z = position.z;
	UINT index[4];
	if (x <0 || x >= width -1)
		return 0.0f;
	if (z < 0 || z >= height - 1)
		return 0.0f;
	index[0] = (x + 0) + width * (z + 0);
	index[1] = (x + 1) + width * (z + 0);
	index[2] = (x + 0) + width * (z + 1);
	index[3] = (x + 1) + width * (z + 1);

	Vector3 vertex[4];
	for (UINT i = 0; i < 4; i++)
	{
		vertex[i] = vertices[index[i]].pos;
	}
	float u = position.x - vertex[0].x;
	float v = position.z - vertex[0].z;

	Vector3 result;

	if (u + v <= 1.0f)
	{
		result = vertex[0] + (vertex[2] - vertex[0]) * u + (vertex[1] - vertex[0]) * v;
		//0,1,2
	}
	else
	{
		result = vertex[3] + (vertex[2] - vertex[3]) * u + (vertex[1] - vertex[3]) * v;

		//1,2,3
	}


	return result.y;
}



void Terrain::CreateMesh()
{

	vector<Vector4> colors; 
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
			vertex.uv.x =        (float)x / (width  - 1);
			vertex.uv.y = 1.0f - (float)z / (height - 1);

			UINT index = x + width * z;
			if (!colors.empty())
				vertex.pos.y = colors[index].x * HEIGHT_SCALE;
			vertices.emplace_back(vertex);
		}
	}
	for (UINT i = 0; i < height- 1; i++)
	{
		for (UINT j = 0; j < width - 1; j++)
		{
			indices.emplace_back((i + 0) * (width) + (j + 0));
			indices.emplace_back((i + 1) * (width) + (j + 0));
			indices.emplace_back((i + 0) * (width) + (j + 1));


			indices.emplace_back((i + 1) * (width) + (j + 0));
			indices.emplace_back((i + 1) * (width) + (j + 1));
			indices.emplace_back((i + 0) * (width) + (j + 1));
		}
	}

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

		float D = 1.0f / (u0 * v1 - v0 * u1);

		Vector3 tangent = D * (e0 * v1 - e1 * v0);

		vertices[index0].tangent += tangent;
		vertices[index1].tangent += tangent;
		vertices[index2].tangent += tangent;
	}

	for (VertexType& vertex : vertices)
	{
		Vector3 T = vertex.tangent;
		Vector3 N = vertex.normal;

		vertex.tangent = Vector3(T - N * Vector3::Dot(N, T)).GetNormalized();

	}
}

