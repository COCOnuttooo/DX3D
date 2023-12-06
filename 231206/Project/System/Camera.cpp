#include "Framework.h"
#include "Camera.h"

Camera::Camera()
{
	viewBuffer = new MatrixBuffer;

}

Camera::~Camera()
{
	delete	viewBuffer;

}

void Camera::Update()
{
	XMVECTOR eye = XMVectorSet(+3, +3, -3, 0);
	XMVECTOR focus = XMVectorSet(+0, +0, +0, 0);
	XMVECTOR up = XMVectorSet(+0, +1, +0, 0);

	viewMatrix = XMMatrixLookAtLH(eye, focus, up);
}

void Camera::Set()
{
	viewBuffer->SetData(viewMatrix);
	viewBuffer->SetVSBuffer(1);
}

