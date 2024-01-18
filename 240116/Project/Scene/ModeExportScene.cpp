#include "Framework.h"
#include "ModeExportScene.h"
ModelExportScene::ModelExportScene()
{
	exporter = new ModelExporter("Knight");
	exporter->ExportMaterial();
	exporter->ExportMesh();
	knight = new Model("Knight");
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
