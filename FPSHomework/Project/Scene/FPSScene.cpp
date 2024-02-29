#include "Framework.h"
#include "FPSScene.h"
FPSScene::FPSScene()
{
	int b;
	for (int i = 0; i < 100; i++)
	{
		b = rand() % 2;
		if (b == 0)
		{
			targets.push_back(new TargetSphere);
		}
		else
			targets.push_back(new TargetCube);

	}
	for (auto& target : targets)
	{
		target->AddEvent(bind(&FPSScene::AddScore, this, placeholders::_1));
	}
	terrain = new Terrain(L"HeightMap/HWHeight.png", L"HeightMap/HWAlpha.png");

	terrain->SetSecondDiffuseMap(L"Landscape/Box.png");

	terrain->GetMaterial()->Load(L"_TextData/Homework.mat");
	terrain->GetMaterial()->SetShader(L"08_Terrain");


	aim = new Quad(Vector2(0.1, 0.1));
	aim->GetMaterial()->SetShader(L"01_Texture");
	aim->GetMaterial()->SetDiffuseMap(L"LandScape/Aim2.png");
	aim->GetMaterial()->SetNormalMap(L"Solid/Black.png");
	aim->GetMaterial()->SetSpecularMap(L"Solid/Black.png");

}

FPSScene::~FPSScene()
{
	delete terrain;
	delete aim;
	for (Target* target : targets)
	{

		delete target;
	}
}

void FPSScene::Update()
{
	timePassed += DELTA_TIME;
	CoolTime();
	Ray ray = CAMERA->ScreenPointToRay(mousePos);
	aim->translation = ray.origin + ray.direction * 0.5f;
	//aim->translation.z += 10.5;
	aim->rotation = CAMERA->rotation;
	aim->Update();
	terrain->Update();
	for (Target* target : targets)
		target->Update();
}

void FPSScene::PreRender()
{
}

void FPSScene::Render()
{
	terrain->Render();
	for (Target* target : targets)
		target->Render();
	aim->Render();
}

void FPSScene::PostRender()
{
	ImGui::Text("Score : %f", score);

	ImGui::Text("Time : %0.2f", timePassed);
	ImGui::Text("score/sec : %0.2f", score/timePassed);
}

void FPSScene::Respawn()
{
	float life = (rand() % 30) / 10.0f + 2;
	float scale = rand() % 10 + 7;
	Vector3 pos;
	pos.x = (rand() % 2000 - scale * 20) / 10.0f + scale * 1.2;
	pos.z = (rand() % 2000 - scale * 20) / 10.0f + scale * 1.2;
	pos.y = 0;
	pos.y = terrain->GetHeight(pos) + rand() % 20  + scale * 1.2;
	for (Target* target : targets)
	{


		if (target->GetIsActive())
		{
			continue;
		}
		else
		{
			
			TargetCube* cube = dynamic_cast<TargetCube*>(target);
			if (cube!= nullptr)
			{
				cube->Respawn(life, pos, scale);
			}
			TargetSphere* sphere = dynamic_cast<TargetSphere*>(target);
			if (sphere != nullptr)
			{
				sphere->Respawn(life, pos, scale);
			}
			break;
		}

	}
}

void FPSScene::CoolTime()
{
	spawnCoolTime -= DELTA_TIME;
	if (spawnCoolTime <= 0)
	{
		spawnCoolTime = (rand() % 10) /10.0f + 0.2;
		Respawn();

	}
}
