#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	viewBuffer = new MatrixBuffer();

	translation.z = -5.0f;
}

Camera::~Camera()
{
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

		if (KEY_PRESS('S'))
		{
			translation += -GetUpVector() * moveSpeed * DELTA_TIME;
		}

		if (KEY_PRESS('W'))
		{
			translation += +GetUpVector() * moveSpeed * DELTA_TIME;
		}

		Vector3 delta = mousePos - oldPos;

		rotation.y += delta.x * 30.0f * DELTA_TIME;
		rotation.x += delta.y * 30.0f * DELTA_TIME;

	}
	oldPos = mousePos;

}

void Camera::Set()
{
	viewMatrix = XMMatrixInverse(nullptr, world);

	viewBuffer->SetData(viewMatrix);
	viewBuffer->SetVSBuffer(1);
}
