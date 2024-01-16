#include "Framework.h"
#include "TerrainEditorScene.h"

TerrainEditorScene::TerrainEditorScene()
{
	editor = new TerrainEditor();
}

TerrainEditorScene::~TerrainEditorScene()
{
	delete editor;
}

void TerrainEditorScene::Update()
{
	editor->Update();
}

void TerrainEditorScene::PreRender()
{
}

void TerrainEditorScene::Render()
{
	editor->Render();
}

void TerrainEditorScene::PostRender()
{
	editor->GetMaterial()->Debug();
	editor->Debug();
}