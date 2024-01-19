#include "Framework.h"
#include "ModeExportScene.h"
ModelExportScene::ModelExportScene()
{
	exporter = new ModelExporter("KnightAnimation/Happy Idle");
	//exporter->ExportMaterial();
	//exporter->ExportMesh();
	//knight = new Model("Groot");
}

ModelExportScene::~ModelExportScene()
{
	delete exporter;
}

void ModelExportScene::Update()
{
	//knight->Update();
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
	//knight->Render();
}

void ModelExportScene::PostRender()
{
	//knight->Debug();
}
