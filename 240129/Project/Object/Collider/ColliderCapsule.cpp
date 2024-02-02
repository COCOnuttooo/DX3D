#include "Framework.h"
#include "ColliderCapsule.h"


ColliderCapsule::ColliderCapsule(float radius, float height, UINT sliceCount, UINT stackCount)
    :radius(radius), height(height), sliceCount(sliceCount), stackCount(stackCount)
{
    CreateMesh();
}

ColliderCapsule::~ColliderCapsule()
{
}

void ColliderCapsule::CreateMesh()
{
	float   phiStep = XM_PI / stackCount;
	float thetaStep = XM_2PI / sliceCount;

	for (UINT i = 0; i < stackCount + 1; i++)
	{
		float phi = i * phiStep;

		for (UINT j = 0; j < sliceCount + 1; j++)
		{
			float theta = j * thetaStep;

			Vertex vertex(0, 0, 0);

			vertex.pos.x = radius * sin(phi) * cos(theta);
			vertex.pos.y = radius * cos(phi);
			vertex.pos.z = radius * sin(phi) * sin(theta);

			if (vertex.pos.y >0)
				vertex.pos.y += height * 0.5f;
			else if (vertex.pos.y < 0)
				vertex.pos.y -= height * 0.5f;

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

bool ColliderCapsule::Collision(IN Ray& ray, OUT HitResult* hitResult)
{
    return false;
}

bool ColliderCapsule::Collision(ColliderBox* other)
{
    return false;
}

bool ColliderCapsule::Collision(ColliderSphere* other)
{
    return false;
}

bool ColliderCapsule::Collision(ColliderCapsule* other)
{
    return false;
}
