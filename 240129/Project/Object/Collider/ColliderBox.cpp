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

bool ColliderBox::Collision(IN Ray& ray, OUT HitResult* hitResult)
{

	Transform::Update();

	HitResult temp;

	temp.distance = FLT_MAX;

	UINT faces[] =
	{
	   0, 1, 2, 3,
	   4, 5, 6, 7,
	   1, 5, 3, 7,
	   0, 4, 2, 6,
	   0, 1, 4, 5,
	   2, 3, 6, 7
	};

	for (UINT i = 0; i < 6; i++)
	{
		Vector3 p[4];

		for (UINT j = 0; j < 4; j++)
		{
			p[j] = vertices[faces[4 * i + j]].pos;
			p[j] = XMVector3TransformCoord(p[j], world);
		}

		float distance = 0.0f;

		if (TriangleTests::Intersects(ray.origin, ray.direction, p[0], p[1], p[2], distance))
		{
			if (temp.distance > distance)
			{
				temp.distance = distance;
				
				temp.impactPoint = ray.origin + ray.direction * distance;
			}
		}

		if (TriangleTests::Intersects(ray.origin, ray.direction, p[3], p[1], p[2], distance))
		{
			if (temp.distance > distance)
			{
				temp.distance = distance;
				temp.impactPoint = ray.origin + ray.direction * distance;
			}
		}
	}

	if (temp.distance == FLT_MAX)
		return false;

	if (hitResult != nullptr)
		*hitResult = temp;

	return true;

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
	for (UINT i = 0; i < 3; i++)
	{
		for (UINT j = 0; j < 3; j++)
		{
			Vector3 cross = Vector3::Cross(box1.axis[i], box2.axis[j]);

			if (SeparatedAxis(D, cross, box1, box2)) return false;
		}
	}
	return true;
}

bool ColliderBox::Collision(ColliderSphere* other)
{
	Matrix R = XMMatrixInverse(nullptr, XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z));

	Matrix T = XMMatrixInverse(nullptr, XMMatrixTranslation(translation.x, translation.y, translation.z));
	
	Matrix changedWorld = T * R * other->GetWorld();
	other->rotation;
	this->rotation;
	OBB box = this->GetOBB();
	Vector3 pos = this->GetGlobalPosition();
	for (UINT i = 0; i < 3; i++)
	{
		float length = Vector3::Dot(box.axis[i], other->GetGlobalPosition() - this->GetGlobalPosition());

		float mult = (length < 0.0f) ? -1.0f : 1.0f;

		length = min(abs(length), box.halfSize[i]);

		pos += box.axis[i] * length * mult;
	}

	float distance = (other->GetGlobalPosition() - pos).Length();


	return distance <= other->Radius();
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
