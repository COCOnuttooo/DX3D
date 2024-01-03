#include "Framework.h"
#include "TerrainEditorScene.h"
TerrainEditorScene::TerrainEditorScene()
{
	editor = new TerrainEditor;
}

TerrainEditorScene::~TerrainEditorScene()
{
	delete editor;
}

void TerrainEditorScene::Update()
{
	editor->Update();
	if (KEY_PRESS(VK_LBUTTON))
	{
		editor->Picking();
	}
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
