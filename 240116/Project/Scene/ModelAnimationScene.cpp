#include "Framework.h"
#include "ModelAnimationScene.h"
ModelAnimationScene::ModelAnimationScene()
{
	model = new ModelAnimator("Knight");
	model->ReadClip("Happy Idle");
	model->ReadClip("Hip Hop Dancing");
	model->ReadClip("Run");
}

ModelAnimationScene::~ModelAnimationScene()
{
	delete model;
}

void ModelAnimationScene::Update()
{
	model->Update();
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
	model->Render();
}

void ModelAnimationScene::PostRender()
{
	model->Debug();
}
