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
