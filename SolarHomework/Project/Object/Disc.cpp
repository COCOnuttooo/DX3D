#include "Framework.h"
#include "Disc.h"


Disc::Disc(float innerRadius, float outerRadius, UINT sliceCount)
	:innerRadius(innerRadius),outerRadius(outerRadius), sliceCount(sliceCount), GameObject(L"03_Diffusetexture")
{
	CreateMesh();
}

Disc::~Disc()
{
}



void Disc::CreateMesh()
{
	
	float thetaStep = XM_2PI*2 / sliceCount;

	for (int j = 0; j < sliceCount + 1; j++)
	{
		float theta = j * thetaStep;
		float xOuter = outerRadius * cos(theta);
		float yOuter = outerRadius * sin(theta);
		//vertices.emplace_back(Vector3{ xOuter, yOuter, 0 });

		// Inner circle points
		float xInner = innerRadius * cos(theta);
		float yInner = innerRadius * sin(theta);
		//vertices.emplace_back(Vector3{ xInner, yInner, 0 });
		VertexType vertex;

		vertex.normal = Vector3(0, 0, -1);
		vertex.pos = Vector3(xInner, yInner, 0);
		vertex.uv = { 0,j / (float)sliceCount };
		vertices.emplace_back(vertex);
		vertex.normal = Vector3(0, 0, -1);
		vertex.pos = Vector3(xOuter, yOuter, 0);
		vertex.uv = { 1.0f, j / (float)sliceCount };
		vertices.emplace_back(vertex);


	}



	for (UINT j = 0; j < sliceCount; j++)
	{
		indices.emplace_back((j + 0));
		indices.emplace_back((j + 3));
		indices.emplace_back((j + 1));

		indices.emplace_back((j + 2));
		indices.emplace_back((j + 3));
		indices.emplace_back((j + 0));
		//indices.emplace_back((i + 0) * (sliceCount + 1) + (j + 0));
		//indices.emplace_back((i + 0) * (sliceCount + 1) + (j + 1));
		//indices.emplace_back((i + 1) * (sliceCount + 1) + (j + 0));


		//indices.emplace_back((i + 1) * (sliceCount + 1) + (j + 0));
		//indices.emplace_back((i + 0) * (sliceCount + 1) + (j + 1));
		//indices.emplace_back((i + 1) * (sliceCount + 1) + (j + 1));
	}
	
	mesh = new Mesh(vertices, indices);
}
