#include "Framework.h"
#include "Transform.h"
Transform::Transform()
{
	worldBuffer = new MatrixBuffer;
	world = XMMatrixIdentity();
}

Transform::~Transform()
{
	delete worldBuffer;

}

void Transform::SetWorld()
{
	worldBuffer->SetData(world);
	worldBuffer->SetVSBuffer(0);
}

void Transform::Update()
{
	UpdateWorldMatrix();
}

void Transform::UpdateWorldMatrix()
{
	Matrix S = XMMatrixScaling(scale.x, scale.y, scale.z);
	Matrix R = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	Matrix T = XMMatrixTranslation(translation.x, translation.y, translation.z);
	Matrix P = XMMatrixTranslation(pivot.x, pivot.y, pivot.z);
	//Matrix IP = -P;
	Matrix IP = XMMatrixTranslation(-pivot.x, -pivot.y, -pivot.z);
	Matrix RP = XMMatrixTranslation(rotPivot.x, rotPivot.y, rotPivot.z);
	Matrix IRP = XMMatrixTranslation(-rotPivot.x, -rotPivot.y, -rotPivot.z);

	world = IP * S * IRP * R * RP * T * P;
	worldNoScale = IP * IRP * R * RP *  T * P;
	if (parent != nullptr)
	{
		world *= parent->worldNoScale;
		worldNoScale *= parent->worldNoScale;
	}
	//world = XMMatrixTransformation(pivot,)

	XMFLOAT4X4 fWorld;

	XMStoreFloat4x4(&fWorld, world);

	right   = Vector3(fWorld._11, fWorld._12, fWorld._13).GetNormalized();
	up      = Vector3(fWorld._21, fWorld._22, fWorld._23).GetNormalized();
	forward = Vector3(fWorld._31, fWorld._32, fWorld._33).GetNormalized();

	
}
