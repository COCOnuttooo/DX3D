#include "Framework.h"
#include "InstancingScene.h"

InstancingScene::InstancingScene()
{
	//for (float x = 0; x < COUNT; x++)
	//{
	//	for (float y = 0; y < COUNT; y++)
	//	{
	//		Quad* quad = new Quad();
	//		quad->GetMaterial()->SetDiffuseMap(L"Landscape/Box.png");
	//		quad->translation = { 2 * x, 2 * y , 1 };
	//		quads.emplace_back(quad);
	//	}
	//}
	quad = new Quad;
	quad->GetMaterial()->SetDiffuseMap(L"Landscape/Box.png");
	quad->GetMaterial()->SetShader(L"12_TextureInstancing");

	for (float x = 0; x < COUNT; x++)
	{
		for (float y = 0; y < COUNT; y++)
		{
			Matrix transform = XMMatrixTranslation(2 * x, 2 * y, 1);
			instanceData.emplace_back(XMMatrixTranspose(transform));
		}
	}
	instanceBuffer = new VertexBuffer(instanceData);
}

InstancingScene::~InstancingScene()
{
	delete quad;
	delete instanceBuffer;
	//for (auto& quad : quads)
	//{
	//	delete quad;
	//}
}

void InstancingScene::Update()
{
	/*for (auto& quad : quads)
		quad->Update();*/
}

void InstancingScene::PreRender()
{
}

void InstancingScene::Render()
{
	//for (auto& quad : quads)
	//	quad->Render();
	instanceBuffer->IASetBuffer(1);
	quad->RenderInstanced(instanceData.size());
}

void InstancingScene::PostRender()
{
}
