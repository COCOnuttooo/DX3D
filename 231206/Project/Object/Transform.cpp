#include "Framework.h"
#include "Transform.h"
Transform::Transform()
{
	worldBuffer = new MatrixBuffer;

}

Transform::~Transform()
{
	delete worldBuffer;

}

void Transform::SetWorld()
{
	worldBuffer->SetData(worldMatrix);
	worldBuffer->SetVSBuffer(0);
}

void Transform::Update()
{
	UpdateWorld();
}

void Transform::UpdateWorld()
{
	worldMatrix = XMMatrixTransformation(pivot,)
}
