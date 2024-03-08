#include "Framework.h"
#include "FrustumCullingScene.h"

FrustumCullingScene::FrustumCullingScene()
{
	for (UINT i = 0; i < SIZE; i++)
	{
		for (UINT j = 0; j < SIZE; j++)
		{
			for (UINT k = 0; k < SIZE; k++)
			{
				Sphere* sphere = new Sphere;
				sphere->translation = Vector3(5 * i, 5 * j, 5 * k);
				sphere->GetMaterial()->SetDiffuseMap(L"Landscape/Box.png");

				spheres.emplace_back(sphere);
			}
		}
	}
	for (auto& sphere : spheres)
		sphere->Update();
}

FrustumCullingScene::~FrustumCullingScene()
{
	for (auto& sphere : spheres)
		delete sphere;
}

void FrustumCullingScene::Update()
{
	for (auto& sphere : spheres)
		sphere->Update();
}

void FrustumCullingScene::PreRender()
{
}

void FrustumCullingScene::Render()
{
	for (auto& sphere : spheres)
	{
		if (!CAMERA->SphereInFrustum( sphere->GetGlobalPosition(), sphere->GetRadius() ))
			continue;
		sphere->Render();
	}
}

void FrustumCullingScene::PostRender()
{
}
