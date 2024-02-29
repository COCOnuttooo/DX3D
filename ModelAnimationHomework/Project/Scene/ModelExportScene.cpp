#include "Framework.h"
#include "ModelExportScene.h"
ModelExportScene::ModelExportScene()
{
	string name = "Racer";
	exporter = new ModelExporter(name);
	exporter->ExportModel();
	exporter->ExportAnimation("Ninja Idle");
	exporter->ExportAnimation("Fast Run");
	exporter->ExportAnimation("Melee Attack");
	//exporter->ExportMaterial();
	//exporter->ExportMesh();
	knight = new Model(name);
}

ModelExportScene::~ModelExportScene()
{
	delete exporter;
	delete knight;
}

void ModelExportScene::Update()
{
	knight->Update();
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
	knight->Render();
}

void ModelExportScene::PostRender()
{
	knight->Debug();
}
