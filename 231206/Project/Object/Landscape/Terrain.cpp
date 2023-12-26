#include "Framework.h"
#include "Terrain.h"
Terrain::Terrain(wstring heightMapFile)
	:GameObject(L"04_Specular")
{
	heightMap = Texture::Add(heightMapFile);
	CreateMesh();
}

Terrain::~Terrain()
{
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
	mesh = new Mesh(vertices, indices);
}

