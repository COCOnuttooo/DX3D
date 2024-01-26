#include "Framework.h"
#include "ModelExportScene.h"
ModelExportScene::ModelExportScene()
{
	exporter = new ModelExporter("deadpool");
	//exporter->ExportModel();
	exporter->ExportAnimation("Goofy Running");
	//exporter->ExportAnimation("Happy Idle");
	//exporter->ExportAnimation("Walk");
	//exporter->ExportMaterial();
	//exporter->ExportMesh();
	knight = new Model("deadpool");
}

ModelExportScene::~ModelExportScene()
{
	//delete exporter;
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
