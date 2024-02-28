#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
	CreatePerspective();

	mainCamera = new Camera();

	lightBuffer = new LightBuffer();
}

Environment::~Environment()
{
	delete lightBuffer;

	delete mainCamera;

	delete persBuffer;
}

void Environment::CreatePerspective()
{
	persBuffer = new MatrixBuffer();

	persMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);
}

void Environment::Update()
{
	mainCamera->Update();
}

void Environment::Set()
{
	mainCamera->Set();

	persBuffer->SetData(persMatrix);
	persBuffer->SetVSBuffer(2);

	lightBuffer->SetPSBuffer(0);
}

void Environment::Debug()
{
	mainCamera->Debug();

	if (ImGui::TreeNode("Light Option"))
	{
		ImGui::DragFloat3("Direction", (float*)&lightBuffer->data.direction, 0.1f, -1, 1);

		ImGui::TreePop();
	}
}
