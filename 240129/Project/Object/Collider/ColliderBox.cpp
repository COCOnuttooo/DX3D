#include "Framework.h"
#include "ColliderBox.h"

ColliderBox::ColliderBox(Vector3 size)
	:size(size)
{
	CreateMesh();
	material->GetBuffer()->data.diffuse = Vector4(1, 0.5, 1, 1);
}

ColliderBox::~ColliderBox()
{
}

void ColliderBox::CreateMesh()
{
	Vector3 halfSize = size * 0.5f;

	vertices =
	{
		{ -halfSize.x ,+halfSize.y, -halfSize.z },
		{ +halfSize.x ,+halfSize.y, -halfSize.z },
		{ -halfSize.x ,-halfSize.y, -halfSize.z },
		{ +halfSize.x ,-halfSize.y, -halfSize.z },

		{ -halfSize.x ,+halfSize.y, +halfSize.z },
		{ +halfSize.x ,+halfSize.y, +halfSize.z },
		{ -halfSize.x ,-halfSize.y, +halfSize.z },
		{ +halfSize.x ,-halfSize.y, +halfSize.z }
	};

	indices =
	{
		0,1, 2,3, 4,5, 6,7,

		0,4, 1,5, 2,6, 3,7,

		0,2, 1,3, 4,6, 5,7
	};

	mesh = new Mesh(vertices, indices);
}

bool ColliderBox::Collision(const IN Ray& ray, OUT HitResult* result)
{
	return false;
}

bool ColliderBox::Collision(ColliderBox* other)
{
	Update();
	OBB box1 = this->GetOBB();
	OBB box2 = other->GetOBB();

	Vector3 D = other->globalPosition - this->globalPosition;
	for (UINT i = 0; i < 3; i++)
	{
		if (SeparatedAxis(D, box1.axis[i], box1, box2)) return false;
		if (SeparatedAxis(D, box2.axis[i], box1,box2)) return false;
			
	}

	return true;
}

bool ColliderBox::Collision(ColliderSphere* other)
{
	return false;
}

bool ColliderBox::Collision(ColliderCapsule* other)
{
	return false;
}

ColliderBox::OBB ColliderBox::GetOBB()
{
	OBB obbData;

	obbData.halfSize = size * 0.5f * globalScale;

	obbData.axis[0] = this->GetRightVector();
	obbData.axis[1] = this->GetUpVector();
	obbData.axis[2] = this->GetForwardVector();
	return obbData;
}

bool ColliderBox::SeparatedAxis(Vector3 distance, Vector3 axis, OBB box1, OBB box2)
{
	float dist = abs(Vector3::Dot(distance, axis));
	float sum = 0.0f;

	for (UINT i = 0; i < 3; i++)
	{
		sum += abs(Vector3::Dot(box1.axis[i] * box1.halfSize[i], axis));
		sum += abs(Vector3::Dot(box2.axis[i] * box2.halfSize[i], axis));
	}
	return dist > sum;
}
