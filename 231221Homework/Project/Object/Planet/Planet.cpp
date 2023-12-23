#include "Framework.h"
#include "Planet.h"
Planet::Planet()
{
	cube = new TextureCube;
	cube->SetParent(this);
}

Planet::~Planet()
{
	delete cube;
}

void Planet::Update()
{
	rotation += rotationSpeed * DELTA_TIME;
	angle += orbitSpeed * DELTA_TIME;
	//rotation2.y += orbitSpeed.y * DELTA_TIME;
	//rotation2.x += orbitSpeed.x * DELTA_TIME;
	UpdateWorldMatrix();
	cube->Update();
}

void Planet::UpdateWorldMatrix()
{
	Matrix S = XMMatrixScaling(scale.x, scale.y, scale.z);

	Matrix R = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	//Matrix R2 = XMMatrixRotationRollPitchYaw(rotation2.x, rotation2.y, rotation2.z);

	Matrix T = XMMatrixTranslation(translation.x, translation.y, translation.z);


	Matrix P = XMMatrixTranslation(pivot.x, pivot.y, pivot.z);
	Matrix IP = XMMatrixInverse(nullptr, P);

	if (parent!=nullptr)
	{
		Matrix R2 = XMMatrixRotationAxis(orbitDir, angle);
		world = IP * S * R * T * R2 * P;
		Matrix temp = static_cast<Planet*>(parent)->GetParentMat();
		Matrix parentWorld = XMMatrixTranslation
		(
			temp.r[3].m128_f32[0],
			temp.r[3].m128_f32[1],
			temp.r[3].m128_f32[2]
		);
		world *= parentWorld;
		
	}
	else
	{
		world = IP * S * R * T * P;
	}

	//if (parent != nullptr)
	//	world *= parent->world;

	XMFLOAT4X4 fWorld;

	XMStoreFloat4x4(&fWorld, world);

	right = Vector3(fWorld._11, fWorld._12, fWorld._13).GetNormalized();
	up = Vector3(fWorld._21, fWorld._22, fWorld._23).GetNormalized();
	forward = Vector3(fWorld._31, fWorld._32, fWorld._33).GetNormalized();
}

void Planet::Render()
{
	cube->Render();
}

void Planet::SetInitialTranslation(Vector3 vec)
{
	translation.x = vec.x;
	translation.y = vec.y;
	translation.z = vec.z;
	
	if (parent != nullptr)
	{

		orbitDir = -Vector3::Cross(Vector3(1, 0, 0),translation).GetNormalized();
		//orbitDir = translation.GetNormalized();
		Vector3::Dot(translation, orbitDir);
	}
}

