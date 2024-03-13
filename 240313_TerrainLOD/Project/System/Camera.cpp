#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	viewBuffer = new ViewBuffer();

	//translation.z = -5.0f;


	LoadData();

	//rotation.x = XM_PIDIV2;
}

Camera::~Camera()
{
	SaveData();

	delete viewBuffer;
}

void Camera::Update()
{
	Transform::Update();

	if (target == nullptr)
		FreeMode();
	else
		TargetMode();

	CalculateFrustum();
}

void Camera::Set()
{
	if (target == nullptr)
		viewMatrix = XMMatrixInverse(nullptr, world);

	viewBuffer->SetData(viewMatrix, world);
	viewBuffer->SetVSBuffer(1);
	viewBuffer->SetPSBuffer(1);
	viewBuffer->SetDSBuffer(1);
	viewBuffer->SetHSBuffer(1);
}

void Camera::SetView()
{
	Transform::Update();

	Camera::Set();
}

void Camera::Debug()
{
	ImGuiIO io = ImGui::GetIO();

	distance -= io.MouseWheel * moveSpeed;

	distance = Clamp(distance, 10.0f, 50.0f);

	if (ImGui::TreeNode("Camera Option"))
	{
		ImGui::Text("Pos :   %d,   %d,   %d", (int)translation.x, (int)translation.y, (int)translation.z);
		ImGui::Text("Rot : %.2f, %.2f, %.2f",         rotation.x,         rotation.y,         rotation.z);

		ImGui::SliderFloat("  Move Speed",   &moveSpeed,  1.0f, 150.0f);
		ImGui::SliderFloat("Rotate Speed", &rotateSpeed, 0.01f, 150.0f);

		ImGui::SliderFloat("Height",   &height,   -10.0f, 150.0f);
		ImGui::SliderFloat("Distance", &distance, -10.0f, 150.0f);

		ImGui::SliderAngle("RotationY", &rotY);

		ImGui::SliderFloat("MoveDamping", &moveDamping, 0.0f, 30.0f);
		ImGui::SliderFloat(" RotDamping", & rotDamping, 0.0f, 30.0f);



		if (ImGui::Button("Set Default"))
		{
			scale       = { 1, 1,   1 };
			rotation    = { 0, 0,   0 };
			translation = { 0, 0, -10 };
		}

		ImGui::TreePop();
	}
}

void Camera::FreeMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		if (KEY_PRESS('A'))
		{
			translation += -GetRightVector() * moveSpeed * DELTA_TIME;
		}

		if (KEY_PRESS('D'))
		{
			translation += +GetRightVector() * moveSpeed * DELTA_TIME;
		}

		if (KEY_PRESS('Q'))
		{
			translation += -GetUpVector() * moveSpeed * DELTA_TIME;
		}

		if (KEY_PRESS('E'))
		{
			translation += +GetUpVector() * moveSpeed * DELTA_TIME;
		}

		if (KEY_PRESS('S'))
		{
			translation += -GetForwardVector() * moveSpeed * DELTA_TIME;
		}

		if (KEY_PRESS('W'))
		{
			translation += +GetForwardVector() * moveSpeed * DELTA_TIME;
		}


		Vector3 delta = mousePos - oldPos;

		rotation.x += -delta.y * rotateSpeed;
		rotation.y += delta.x * rotateSpeed;

	}

	oldPos = mousePos;
}

void Camera::TargetMode()
{
	if (KEY_PRESS(VK_RBUTTON))
	{
		Vector3 delta = mousePos - oldPos;

		rotation.x += -delta.y * rotateSpeed;
		rotation.y +=  delta.x * rotateSpeed;
	}

	oldPos = mousePos;

	destRotY = LERP(destRotY, this->rotation.y, DELTA_TIME * rotDamping);
	destRotX = LERP(destRotX, this->rotation.x, DELTA_TIME * rotDamping);
	
	rotMatrix = XMMatrixRotationRollPitchYaw(destRotX, destRotY + rotY, 0.0f);
	
	Vector3 backward = XMVector3TransformNormal(Vector3(0, 0, -1), rotMatrix);
	
	destPos  = target->GetGlobalPosition() + backward * distance + Vector3(0, 1, 0) * height;
	
	translation = LERP(translation, destPos, DELTA_TIME * moveDamping);
	
	Vector3 targetPos = target->GetGlobalPosition();

	targetPos.y += height;

	viewMatrix = XMMatrixLookAtLH(translation, targetPos, Vector3(0, 1, 0));
}

void Camera::SaveData()
{
	BinaryWriter data("_TextData/Camera.data");

	data.WriteData(scale);
	data.WriteData(rotation);
	data.WriteData(translation);

	data.WriteData(moveSpeed);
	data.WriteData(rotateSpeed);
}

void Camera::LoadData()
{
	BinaryReader data("_TextData/Camera.data");

	if (!data.Succeeded())
		return;

	scale       = data.ReadVector3();
	rotation    = data.ReadVector3();
	translation = data.ReadVector3();

	  moveSpeed = data.ReadFloat();
	rotateSpeed = data.ReadFloat();
}

Ray Camera::ScreenPointToRay(Vector3 screenPoint)
{
	Vector3 screenSize(WIN_WIDTH, WIN_HEIGHT, 1.0f);

	//Inv Viewport
	Vector3 point;
	point.x = (screenPoint.x / screenSize.x) * 2.0f - 1.0f;
	point.y = (screenPoint.y / screenSize.y) * 2.0f - 1.0f;
	//point.y *= -1;
	point.z = 1.0f;

	//Inv Projection

	//XMFLOAT4X4 projection;
	//XMStoreFloat4x4(&projection, ENVIRONMENT->GetPersMatrix());

	Matrix invProj = XMMatrixInverse(nullptr, ENVIRONMENT->GetPersMatrix());

	point = XMVector3TransformCoord(point, invProj);

	//Inv View

	point = XMVector3TransformCoord(point, world);

	Ray ray;

	ray.origin    = globalPosition;
	ray.direction = Vector3(point - globalPosition).GetNormalized();

	return ray;
}

Vector3 Camera::WorldToScreenPos(Vector3 worldPos)
{
	Vector3 screenPos;

	screenPos = XMVector3TransformCoord( worldPos, viewMatrix);
	screenPos = XMVector3TransformCoord(screenPos, ENVIRONMENT->GetPersMatrix());

	screenPos += Vector3(1, 1, 1);
	screenPos *= 0.5f;

	screenPos.x *= WIN_WIDTH;
	screenPos.y *= WIN_HEIGHT;

	return screenPos;
}

bool Camera::PointInFrustum(Vector3 point)
{
	for (UINT i = 0; i < 6; i++)
	{
		Vector3 dot = XMPlaneDotCoord(planes[i], point);

		if (dot.x < 0.0f)
			return false;
	}

	return true;
}

bool Camera::SphereInFrustum(Vector3 center, float radius)
{
	Vector3 edge;
	Vector3 dot;

	for (UINT i = 0; i < 6; i++)
	{
		edge.x = center.x - radius;
		edge.y = center.y - radius;
		edge.z = center.z - radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x + radius;
		edge.y = center.y - radius;
		edge.z = center.z - radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x - radius;
		edge.y = center.y + radius;
		edge.z = center.z - radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x - radius;
		edge.y = center.y - radius;
		edge.z = center.z + radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;


		edge.x = center.x + radius;
		edge.y = center.y + radius;
		edge.z = center.z - radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x + radius;
		edge.y = center.y - radius;
		edge.z = center.z + radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x - radius;
		edge.y = center.y + radius;
		edge.z = center.z + radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;

		edge.x = center.x + radius;
		edge.y = center.y + radius;
		edge.z = center.z + radius;

		dot = XMPlaneDotCoord(planes[i], edge);
		if (dot.x > 0.0f)
			continue;


		return false;
	}

	return true;
}

void Camera::CalculateFrustum()
{
	XMFLOAT4X4 VP;

	XMStoreFloat4x4(&VP, viewMatrix * ENVIRONMENT->GetPersMatrix());

	//Left
	a = VP._14 + VP._11;
	b = VP._24 + VP._21;
	c = VP._34 + VP._31;
	d = VP._44 + VP._41;

	planes[0] = XMVectorSet(a, b, c, d);

	//Right
	a = VP._14 - VP._11;
	b = VP._24 - VP._21;
	c = VP._34 - VP._31;
	d = VP._44 - VP._41;

	planes[1] = XMVectorSet(a, b, c, d);

	//Bottom
	a = VP._14 + VP._12;
	b = VP._24 + VP._22;
	c = VP._34 + VP._32;
	d = VP._44 + VP._42;

	planes[2] = XMVectorSet(a, b, c, d);

	//Top
	a = VP._14 - VP._12;
	b = VP._24 - VP._22;
	c = VP._34 - VP._32;
	d = VP._44 - VP._42;

	planes[3] = XMVectorSet(a, b, c, d);


	//Near
	a = VP._14 + VP._13;
	b = VP._24 + VP._23;
	c = VP._34 + VP._33;
	d = VP._44 + VP._43;

	planes[4] = XMVectorSet(a, b, c, d);

	//Far
	a = VP._14 - VP._13;
	b = VP._24 - VP._23;
	c = VP._34 - VP._33;
	d = VP._44 - VP._43;

	planes[5] = XMVectorSet(a, b, c, d);

	for (UINT i = 0; i < 6; i++)
	{
		planes[i] = XMPlaneNormalize(planes[i]);
	}
}
