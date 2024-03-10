#include "Framework.h"
#include "Environment.h"

Environment::Environment()
{
	CreatePerspective();
	CreateOrthographic();

	mainCamera = new Camera();

	lightBuffer = new LightBuffer();
}

Environment::~Environment()
{
	delete lightBuffer;

	delete mainCamera;

	delete persBuffer;

	delete UIViewBuffer;
	delete orthoBuffer;
}

void Environment::CreatePerspective()
{
	persBuffer = new MatrixBuffer();

	persMatrix = XMMatrixPerspectiveFovLH(XM_PIDIV4, WIN_WIDTH / WIN_HEIGHT, 0.1f, 1000.0f);
}

void Environment::CreateOrthographic()
{
	orthoMatrix = XMMatrixOrthographicOffCenterLH
	(
		0.0f, WIN_WIDTH,
		0.0f, WIN_HEIGHT,
		0.0f, 1.0f
	);
	orthoBuffer = new MatrixBuffer;
	orthoBuffer->SetData(orthoMatrix);

	UIViewBuffer = new ViewBuffer;

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

void Environment::PostSet()
{
	UIViewBuffer->SetVSBuffer(1);
	orthoBuffer->SetVSBuffer(2);

	//TODO : ALPHA BLEND


}

void Environment::Debug()
{
	mainCamera->Debug();

	if (ImGui::TreeNode("Light Option"))
	{
		//ImGui::DragFloat3("Direction", (float*)&lightBuffer->data.direction, 0.1f, -1, 1);
		if (ImGui::Button("Add"))
			lightBuffer->data.lightCount++;
		for (UINT i = 0; i < lightBuffer->data.lightCount; i++)
		{
			DebugLight(i);
		}

		ImGui::ColorEdit3("AmbientLight", (float*)&lightBuffer->data.ambientLight);
		ImGui::ColorEdit3("AmbientCeil", (float*)&lightBuffer->data.ambientCeil);

		ImGui::TreePop();
	}
}

void Environment::DebugLight(int lightIndex)
{
	string name = "Light_" + to_string(lightIndex);

	LightData& light = lightBuffer->data.lights[lightIndex];

	if (ImGui::TreeNode(name.c_str()))
	{
		ImGui::Checkbox("Active", (bool*)&light.active);
		const char* list[] = { "Directional", "Point", "Spot", "Capsule" };
		ImGui::Combo("Type", &light.type, list, 4);

		ImGui::ColorEdit4("Color", (float*)&light.color);
		if (light.type == 0)
		{
			ImGui::SliderFloat3("Direction", (float*)&light.direction, -1, 1);

		}
		else
		{
			if (light.type != 1)
				ImGui::SliderFloat3("Direction", (float*)&light.direction, -1, 1);

			ImGui::DragFloat3("Position", (float*)&light.position);

			ImGui::SliderFloat("Range", &light.range, 1, 1000);
			if (light.type == 2)
			{
				ImGui::SliderFloat("InnerRange", &light.innerRange, 0, light.outerRange);
				ImGui::SliderFloat("OuterRange", &light.outerRange, light.innerRange, 180.0f);
			}
			if (light.type == 3)
				ImGui::SliderFloat("Length", &light.length, 0, 500.0f);
		}
		




		ImGui::TreePop();
	}
}