#include "Framework.h"
#include "BillboardScene.h"

BillboardScene::BillboardScene()
{
	terrain = new Terrain(L"HeightMap/HeightMap.png");
	terrain->GetMaterial()->SetDiffuseMap(L"Landscape/Dirt2.png");
	terrain->translation.y = 0.1;
	/*for (UINT i = 0; i < 10000; i++)
	{
		Vector2 size;

		size.x = Random(3.0f, 10.0f);
		size.y = Random(3.0f, 10.0f);

		Vector3 pos;

		pos.x =Random(0.0f, terrain->GetSize().x);
		pos.z =Random(0.0f, terrain->GetSize().y);
		pos.y = terrain->GetHeight(pos) + size.y * 0.5f;

		Quad* quad = new Quad(size);
		quad->GetMaterial()->SetDiffuseMap(L"Landscape/Tree.png");
		quad->GetMaterial()->SetShader(L"01_Texture");

		quad->translation = pos;

		trees.emplace_back(quad);

	}*/
	material = new Material();
	material->SetShader(L"21_Billboard");
	material->SetDiffuseMap(L"Landscape/Tree.png");

	geometryShader = Shader::AddGS(L"21_Billboard");

	for (UINT i = 0; i < MAX_COUNT; i++)
	{
		Vector2 size;

		size.x = Random(3.0f, 10.0f);
		size.y = Random(3.0f, 10.0f);

		Vector3 pos;

		pos.x = Random(0.0f, terrain->GetSize().x);
		pos.z = Random(0.0f, terrain->GetSize().y);
		pos.y = terrain->GetHeight(pos) + size.y * 0.5f;

		VertexTexture vertex;

		vertex.pos = pos;
		vertex.uv = size;

		vertices.emplace_back(vertex);
	}

	//drawVertices

	vertexBuffer = new VertexBuffer(vertices);


}


BillboardScene::~BillboardScene()
{
	delete terrain;
	delete material;
	delete vertexBuffer;

	//for (auto& tree : trees)
	//{
	//	delete tree;
	//}

}

void BillboardScene::Update()
{
	terrain->Update();
	//for (auto& tree : trees)
	//{
	//	//tree->rotation.y = CAMERA->rotation.y;

	//	Vector3 dir = -(CAMERA->GetGlobalPosition() - tree->GetGlobalPosition()).GetNormalized();
	//	float angle = atan2f(dir.x, dir.z) ;
	//	tree->rotation.y = angle;
	//	tree->Update();
	//}
}

void BillboardScene::PreRender()
{
}

void BillboardScene::Render()
{
	STATE->EnableAlphaToCoverage();


	vertexBuffer->IASetBuffer(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	material->Set();
	geometryShader->SetShader();
	DC->Draw(drawCount,0);
	DC->GSSetShader(nullptr, nullptr, 0);
	//for (auto& tree : trees)
	//	tree->Render();
	STATE->DisableAlpha();

	
	terrain->Render();

}

void BillboardScene::PostRender()
{
}
