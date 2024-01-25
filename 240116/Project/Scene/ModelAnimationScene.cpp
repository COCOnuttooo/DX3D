#include "Framework.h"
#include "ModelAnimationScene.h"
ModelAnimationScene::ModelAnimationScene()
{
	model = new ModelAnimator("Knight");
	model->ReadClip("Happy Idle");
	model->ReadClip("Hip Hop Dancing");
	model->ReadClip("Run");

	chicken = new Model("ChickenBlade");
	chicken->AttachToBone(model, "mixamorig:RightHand");
}

ModelAnimationScene::~ModelAnimationScene()
{
	delete model;
	delete chicken;
}

void ModelAnimationScene::Update()
{
	
	model->Update();
	chicken->Update();
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
	//chicken->GetWorld() = model->GetTransformByBone("mixamorig:RightHand");
	model->Render();
	chicken->Render();
}

void ModelAnimationScene::PostRender()
{
	model->Debug();
	chicken->Debug();
}
