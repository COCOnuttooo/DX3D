#include "Framework.h"
#include "ModeExportScene.h"
ModelExportScene::ModelExportScene()
{
	exporter = new ModelExporter("Knight");
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
