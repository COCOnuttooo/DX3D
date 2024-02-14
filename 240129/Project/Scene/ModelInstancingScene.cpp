#include "Framework.h"
#include "ModelInstancingScene.h"

ModelInstancingScene::ModelInstancingScene()
{
	model = new ModelInstancing("Knight");
	for (float x = 0; x < 10; x++)
	{
		for (float z = 0; z < 10; z++)
		{
			Transform* transform = model->AddTransform();
			transform->translation = { x * 10 , 0, z * 10 };

			transform->scale *= 0.05f;
			transform->rotation.y = (10* x + z) / 100 * XM_PI * 2;
		
		}
	}
}

ModelInstancingScene::~ModelInstancingScene()
{
	delete model;
}

void ModelInstancingScene::Update()
{
	model->Update();
}

void ModelInstancingScene::PreRender()
{
}

void ModelInstancingScene::Render()
{
	model->Render();
}

void ModelInstancingScene::PostRender()
{
	model->Debug();
}
