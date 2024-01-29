#include "Framework.h"
#include "Collider.h"
Collider::Collider()
	:GameObject(L"10_Collider")
{
}

Collider::~Collider()
{
}

void Collider::Render()
{
	if (!isActive)
	{
		return;
	}
	GameObject::Render(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

