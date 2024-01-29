#include "Framework.h"
#include "ColliderSphere.h"


ColliderSphere::ColliderSphere(float radius, UINT stackCount, UINT sliceCount)
	:radius(radius),stackCount(stackCount),sliceCount(sliceCount)
{
	CreateMesh();
}

ColliderSphere::~ColliderSphere()
{
}

void ColliderSphere::CreateMesh()
{
	float   phiStep = XM_PI / stackCount;
	float thetaStep = XM_2PI / sliceCount;

	for (UINT i = 0; i < stackCount + 1; i++)
	{
		float phi = i * phiStep;

		for (UINT j = 0; j < sliceCount + 1; j++)
		{
			float theta = j * thetaStep;

			Vertex vertex(0,0,0);

			vertex.pos.x = radius * sin(phi) * cos(theta);
			vertex.pos.y = radius * cos(phi);
			vertex.pos.z = radius * sin(phi) * sin(theta);



			vertices.emplace_back(vertex);
		}
	}

	for (UINT i = 0; i < stackCount; i++)
	{
		for (UINT j = 0; j < sliceCount; j++)
		{
			indices.emplace_back((i + 0) * (sliceCount + 1) + (j + 0));
			indices.emplace_back((i + 1) * (sliceCount + 1) + (j + 0));

			indices.emplace_back((i + 0) * (sliceCount + 1) + (j + 0));
			indices.emplace_back((i + 0) * (sliceCount + 1) + (j + 1));

		}
	}


	mesh = new Mesh(vertices, indices);
}

