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

float Terrain::GetHeight(float x, float z)
{
	UINT index = (int)x + (int)z * height;
	UINT upIndex = (int)x + ((int)z +1) * (height);
	UINT downIndex = (int)x + ((int)z-1) * (height);
	UINT leftIndex = (int)x + (int)z * height - 1;
	UINT rightIndex = (int)x + (int)z * height + 1;
	float interpolatedHeight;
	float curHeight;
	float upHeight;
	float downHeight;
	float leftHeight;
	float rightHeight;
	if (upIndex > vertices.size() || upIndex < 0)
		upHeight = 0;
	else
		upHeight = vertices[upIndex].pos.y;

	if (downIndex > vertices.size() || downIndex < 0)
		downHeight = 0;
	else
		downHeight = vertices[downIndex].pos.y;

	if (leftIndex > vertices.size() || leftIndex < 0)
		leftHeight = 0;
	else
		leftHeight = vertices[leftIndex].pos.y;

	if (rightIndex > vertices.size() || rightIndex < 0)
		rightHeight = 0;
	else
		rightHeight = vertices[rightIndex].pos.y;
	float percentX = x - (int)x;
	float percentZ = z - (int)z;
	// 선형 보간 수식 필요
	float xInterpolated = leftHeight * (1 - percentX) + rightHeight * percentX;
	float zInterpolated = downHeight * (1 - percentZ) + upHeight * percentZ;

	interpolatedHeight = (xInterpolated + zInterpolated) / 2.0f;
	//return vertices[index].pos.y;
	return interpolatedHeight;
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

