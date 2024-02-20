#include "Framework.h"
#include "ModelAnimationScene.h"

ModelAnimationScene::ModelAnimationScene()
{
	model = new ModelAnimator("Knight");
	model->ReadClip("Fast Run");
	model->ReadClip("Happy Idle");
	model->ReadClip("Hip Hop Dancing");

	//model->GetClip(0)->AddEvent(0.5f, bind(&ModelAnimationScene::PlayNextClip, this));
	//model->GetClip(1)->AddEvent(0.5f, bind(&ModelAnimationScene::PlayNextClip, this));
	//model->GetClip(2)->AddEvent(0.5f, bind(&ModelAnimationScene::PlayNextClip, this));

	model->GetClip(0)->AddEvent(0.5f, bind(&ModelAnimationScene::PlayClip, this, 0));
	model->GetClip(1)->AddEvent(0.5f, bind(&ModelAnimationScene::PlayClip, this, 0));
	model->GetClip(2)->AddEvent(0.5f, bind(&ModelAnimationScene::PlayClip, this, 0));

	model->PlayClip(0, 0.1f);

	sword = new Model("Sword");
	sword->AttachToBone(model, "mixamorig:RightHand");
}

ModelAnimationScene::~ModelAnimationScene()
{
	delete model;
	delete sword;
}

void ModelAnimationScene::Update()
{
	model->Update();
	sword->Update();
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
	model->Render();
	sword->Render();
}

void ModelAnimationScene::PostRender()
{
	model->Debug();
	sword->Debug();
}

void ModelAnimationScene::PlayNextClip()
{
	static int index = 1;

	model->PlayClip(index);

	++index %= 3;
}

void ModelAnimationScene::PlayClip(int index)
{
	model->PlayClip(index, 0.1f);
}
