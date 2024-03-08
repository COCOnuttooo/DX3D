#include "Framework.h"
#include "ModelExportScene.h"

ModelExportScene::ModelExportScene()
{
	exporter = new ModelExporter("StanfordBunny");
	exporter->ExportModel();	
	//exporter->ExportAnimation("Hip Hop Dancing");
	//exporter->ExportAnimation("Fast Run");
	//exporter->ExportAnimation("Happy Idle");
}

ModelExportScene::~ModelExportScene()
{
	delete exporter;
}

void ModelExportScene::Update()
{
}

void ModelExportScene::PreRender()
{
}

void ModelExportScene::Render()
{
}

void ModelExportScene::PostRender()
{
}
