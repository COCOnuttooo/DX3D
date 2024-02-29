#include "Framework.h"
#include "ModelAnimationScene.h"
ModelAnimationScene::ModelAnimationScene()
{
	model = new ModelAnimator("Racer");
	model->ReadClip("Ninja Idle");
	model->ReadClip("Fast Run");
	model->ReadClip("Melee Attack");

	//chicken = new Model("ChickenBlade");
	//chicken->AttachToBone(model, "mixamorig:RightHand");

	//model->Getclip(0)->AddEvent(0.5, bind(&ModelAnimationScene::PlayNextClip, this));
	//model->Getclip(1)->AddEvent(0.5, bind(&ModelAnimationScene::PlayNextClip, this));
	//model->Getclip(2)->AddEvent(0.5, bind(&ModelAnimationScene::PlayNextClip, this));


	//model->Getclip(0)->AddEvent(0.5, bind(&ModelAnimationScene::PlayClip, this,1));
	//model->Getclip(1)->AddEvent(0.5, bind(&ModelAnimationScene::PlayClip, this,2));
	//model->Getclip(2)->AddEvent(0.5, bind(&ModelAnimationScene::PlayClip, this,0));
}

ModelAnimationScene::~ModelAnimationScene()
{
	delete model;
	//delete chicken;
}

void ModelAnimationScene::Update()
{
	
	model->Update();
	//chicken->Update();
}

void ModelAnimationScene::PreRender()
{
}

void ModelAnimationScene::Render()
{
	//chicken->GetWorld() = model->GetTransformByBone("mixamorig:RightHand");
	model->Render();
	//chicken->Render();
}

void ModelAnimationScene::PostRender()
{
	model->Debug();
	//chicken->Debug();
}

void ModelAnimationScene::PlayNextClip()
{
	static int index = 0;
	
	model->PlayClip(index);

	++index %= 3;

}

void ModelAnimationScene::PlayClip(int num)
{
	model->PlayClip(num, 1.0f);
}
