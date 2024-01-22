#include "Framework.h"
#include "ModelExportScene.h"
ModelExportScene::ModelExportScene()
{
	exporter = new ModelExporter("SpiderMan");
	exporter->ExportModel();
	//exporter->ExportAnimation("Hip Hop Dancing");
	//exporter->ExportMaterial();
	//exporter->ExportMesh();
	knight = new Model("SpiderMan");
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
