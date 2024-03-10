#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	string name = "Rock";
	exporter = new ModelExporter(name);
	exporter->ExportModel();	
	model = new Model(name);
	//exporter->ExportAnimation("Hip Hop Dancing");
	//exporter->ExportAnimation("Fast Run");
	//exporter->ExportAnimation("Happy Idle");
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
