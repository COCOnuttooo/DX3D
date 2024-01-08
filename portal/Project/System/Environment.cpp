#include "Framework.h"
#include "Environment.h"


Environment::Environment()
{
	CreatePerspective();

	mainCamera = new Camera();
	p1Camera = new Camera();
	p2Camera = new Camera();
	p1Camera->translation = Vector3(0, 0, 0);
	p2Camera->translation = Vector3(0, 0, 0);
	p1Camera->rotation = Vector3(0, 0, 0);
	p2Camera->rotation = Vector3(0, 0, 0);

	lightBuffer = new LightBuffer;
}

Environment::~Environment()
{
	delete lightBuffer;
	delete persBuffer;
	delete mainCamera;
	delete p1Camera;
	delete p2Camera;
}

void Environment::CreatePerspective()
{
	persBuffer = new MatrixBuffer();

	persMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);
}

void Environment::Update()
{
	mainCamera->Update();
	p1Camera->Update();
	p2Camera->Update();
	//p1Camera->rotation = Vector3(mainCamera->GetGlobalPosition() - p1Camera->GetGlobalPosition()).GetNormalized();
	//p2Camera->rotation = Vector3(mainCamera->GetGlobalPosition() - p2Camera->GetGlobalPosition()).GetNormalized();
}

void Environment::Set()
{
	mainCamera->Set();

	persBuffer->SetData(persMatrix);
	persBuffer->SetVSBuffer(2);

	lightBuffer->SetPSBuffer(0);
}

void Environment::SetP1()
{
	p1Camera->Set();

	persBuffer->SetData(persMatrix);
	persBuffer->SetVSBuffer(2);

	lightBuffer->SetPSBuffer(0);
}

void Environment::SetP2()
{
	p2Camera->Set();

	persBuffer->SetData(persMatrix);
	persBuffer->SetVSBuffer(2);

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
