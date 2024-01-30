#include "Framework.h"
#include "ColliderCapsule.h"
ColliderCapsule::ColliderCapsule()
{
}

ColliderCapsule::~ColliderCapsule()
{
}

void ColliderCapsule::CreateMesh()
{
}

bool ColliderCapsule::Collision(const IN Ray& ray, OUT HitResult* result)
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
