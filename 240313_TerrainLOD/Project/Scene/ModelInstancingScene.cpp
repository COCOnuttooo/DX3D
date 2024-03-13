#include "Framework.h"
#include "ModelInstancingScene.h"

ModelInstancingScene::ModelInstancingScene()
{
	model = new ModelAnimatorInstancing("Knight");
	model->ReadClip("Happy Idle");
	model->ReadClip("Fast Run");
	model->ReadClip("Hip Hop Dancing");

	for (float x = 0; x < 10; x++)
	{
		for (float z = 0; z < 10; z++)
		{
			Transform* transform = model->AddTransform();

			transform->translation = { x * 10, 0, z * 10 };
			transform->scale *= 0.05f;
		}
	}

	sky = new SkyBox(L"Landscape/Test.dds");
}

ModelInstancingScene::~ModelInstancingScene()
{
	delete model;

	delete sky;
}

void ModelInstancingScene::Update()
{
	model->Update();

	sky->Update();
}

void ModelInstancingScene::PreRender()
{
}

void ModelInstancingScene::Render()
{
	sky->Render();

	model->Render();
}

void ModelInstancingScene::PostRender()
{
	//model->Debug();
}
