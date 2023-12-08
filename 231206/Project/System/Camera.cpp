#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	translation.z = -5;
	viewBuffer = new MatrixBuffer;

}

Camera::~Camera()
{
	delete	viewBuffer;

}

void Camera::Update()
{
	//XMVECTOR eye = XMVectorSet(+3, +3, -3, 0);
	//XMVECTOR focus = XMVectorSet(+0, +0, +0, 0);
	//XMVECTOR up = XMVectorSet(+0, +1, +0, 0);
	Transform::Update();
	//viewMatrix = XMMatrixLookAtLH(eye, focus, up);
	if (KEY_PRESS(VK_RBUTTON))
	{

		if (KEY_PRESS('A'))
		{
			translation += -GetRightVector() * moveSpeed * DELTA_TIME;
		}
		if (KEY_PRESS('D'))
		{
			translation += GetRightVector() * moveSpeed * DELTA_TIME;
		}
		if (KEY_PRESS('S'))
		{
			translation += -GetUpVector() * moveSpeed * DELTA_TIME;
		}
		if (KEY_PRESS('W'))
		{
			translation += GetUpVector() * moveSpeed * DELTA_TIME;
		}
		Vector3 delta = oldPos - mousePos;
		rotation.y += delta.x * DELTA_TIME * 5;
		rotation.x += delta.y * DELTA_TIME * 5;
	}
	oldPos = mousePos;



}

void Camera::Set()
{
	viewMatrix = XMMatrixInverse(nullptr, world);
	viewBuffer->SetData(viewMatrix);
	viewBuffer->SetVSBuffer(1);
}

