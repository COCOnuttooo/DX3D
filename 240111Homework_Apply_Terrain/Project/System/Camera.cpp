#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	viewBuffer = new ViewBuffer();

	translation.z = -5.0f;

	LoadData();
}

Camera::~Camera()
{
	SaveData();
	delete viewBuffer;
}

void Camera::Update()
{
	Transform::Update();

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

		rotation.y += delta.x * rotateSpeed;// * DELTA_TIME;
		rotation.x += delta.y * rotateSpeed;// * DELTA_TIME;

	}
	oldPos = mousePos;

}

void Camera::Set()
{
	viewMatrix = XMMatrixInverse(nullptr, world);

	viewBuffer->SetData(viewMatrix, world);
	viewBuffer->SetVSBuffer(1);
}

void Camera::Debug()
{
	if (ImGui::TreeNode("CameraOption"))
	{
		ImGui::Text("Pos : %d, %d, %d", (int)translation.x, (int)translation.y, (int)translation.z);
		ImGui::Text("Rot : %.2f, %.2f, %.2f", rotation.x,rotation.y,rotation.z);
		ImGui::SliderFloat("Move Speed",     &moveSpeed, 1.0f, 150.0f);
		ImGui::SliderFloat("Rotate Speed", &rotateSpeed, 0.01f, 150.0f);
		if (ImGui::Button("Set Default"))
		{
			scale = { 1,1,1 };
			rotation = { 0,0,0 };
			translation = { 0,0,-10 };
		}
		ImGui::TreePop();
	}
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
	scale = data.ReadVector3();
	rotation = data.ReadVector3();
	translation = data.ReadVector3();
	moveSpeed = data.ReadFloat();
	rotateSpeed = data.ReadFloat();
}

Ray Camera::ScreenPointToRay(Vector3 screenPoint)
{
	Vector3 screenSize(WIN_WIDTH, WIN_HEIGHT, 1.0f);
	Vector3 point;

	//Inv Viewport
	point.x = (screenPoint.x / screenSize.x) * 2 - 1.0f;
	point.y = (screenPoint.y / screenSize.y)* 2 - 1.0f;
	point.y *= -1;
	point.z = 1.f;
	//Inv Projection
	Matrix invProj = XMMatrixInverse(nullptr, ENVIRONMENT->GetPersMatrix());

	point = XMVector3TransformCoord(point, invProj);
	 
	//XMFLOAT4X4 projection;

	//XMStoreFloat4x4(&projection, XMMatrixInverse(nullptr,ENVIRONMENT->GetPersMatrix()));
	//Inv View
	//Matrix invView = XMMatrixInverse(nullptr, world);
	point = XMVector3TransformCoord(point, world);
	Ray ray;
	ray.origin = globalPosition;
	ray.direction = Vector3(point - globalPosition).GetNormalized();
	return ray;
}
