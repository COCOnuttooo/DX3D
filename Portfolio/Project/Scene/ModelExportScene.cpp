#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "DragonHead";
	exporter = new ModelExporter(name);
	exporter->ExportModel();	
	//exporter->ExportAnimation("Hip Hop Dancing");
	//exporter->ExportAnimation("Fast Run");
	//exporter->ExportAnimation("Happy Idle");
	model = new Model(name);
}

ModelExportScene::~ModelExportScene()
{
	delete exporter;
	delete model;
}

void ModelExportScene::Update()
{
	model->Update();
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
	model->Render();
}

void ModelExportScene::PostRender()
{
	model->Debug();
}
