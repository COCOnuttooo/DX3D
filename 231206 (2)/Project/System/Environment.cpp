#include "Framework.h"
#include "Environment.h"


Environment::Environment()
{
	CreatePerspective();

	mainCamera = new Camera();

	lightBuffer = new LightBuffer;
}

Environment::~Environment()
{
	delete lightBuffer;
	delete projBuffer;
	delete mainCamera;
}

void Environment::CreatePerspective()
{
	projBuffer = new MatrixBuffer();

	projMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);
}

void Environment::Update()
{
	mainCamera->Update();
}

void Environment::Set()
{
	mainCamera->Set();

	projBuffer->SetData(projMatrix);
	projBuffer->SetVSBuffer(2);

	lightBuffer->SetPSBuffer(0);
}

void Environment::Debug()
{
	mainCamera->Debug();
	if (ImGui::TreeNode("Light Option"))
	{
		ImGui::DragFloat3("Direction", (float*)&lightBuffer->data.direction , 0.1f, -1,1);
		ImGui::TreePop();
	}
}
