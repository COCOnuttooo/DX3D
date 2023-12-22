#include "Framework.h"
#include "Sphere.h"


Sphere::Sphere(float radius, UINT sliceCount, UINT stackCount)
	:radius(radius), sliceCount(sliceCount), stackCount(stackCount), GameObject(L"04_Specular")
{
	CreateMesh();
}

Sphere::~Sphere()
{
}



void Sphere::CreateMesh()
{
	float phiStep = XM_PI / stackCount;
	float thetaStep = XM_2PI / sliceCount;
	for (UINT i = 0; i < stackCount+1; i++)
	{
		float phi = i * phiStep;

		for (UINT j = 0; j < sliceCount + 1; j++)
		{
			float theta = j * thetaStep;

			VertexType vertex;

			vertex.pos.x = radius * sin(phi) * cos(theta);
			vertex.pos.y = radius * cos(phi);
			vertex.pos.z = radius * sin(phi) * sin(theta);

			vertex.uv.x = j / (float)sliceCount;
			vertex.uv.y = i / (float)stackCount;

			vertex.normal = vertex.pos/ radius;

			vertices.emplace_back(vertex);


		}
	}

	for (UINT i = 0; i < stackCount; i++)
	{
		for (UINT j = 0; j < sliceCount; j++)
		{
			indices.emplace_back((i + 0) * (sliceCount + 1) + (j + 0));
			indices.emplace_back((i + 0) * (sliceCount + 1) + (j + 1));
			indices.emplace_back((i + 1) * (sliceCount + 1) + (j + 0));


			indices.emplace_back((i + 1) * (sliceCount + 1) + (j + 0));
			indices.emplace_back((i + 0) * (sliceCount + 1) + (j + 1));
			indices.emplace_back((i + 1) * (sliceCount + 1) + (j + 1));
		}
	}
	mesh = new Mesh(vertices, indices);
}
