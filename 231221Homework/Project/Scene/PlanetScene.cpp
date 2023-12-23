#include "Framework.h"
#include "PlanetScene.h"
PlanetScene::PlanetScene()
{

	for (int i = 0; i < 3; i++)
	{
		planets.push_back(new Planet);
	}
	for (UINT i = 1; i < 2; i++)
	{
		planets[i]->SetParent(planets[0]);
		CreateRandomOrbit(planets[i], i * 10);
	}
	planets[2]->SetParent(planets[1]);
	CreateRandomOrbit(planets[2], 5);
	
}

PlanetScene::~PlanetScene()
{
	for (auto& i : planets)
	{
		delete i;
	}
	planets.clear();
}

void PlanetScene::Update()
{

	for (auto& i : planets)
	{
		i->Update();
	}
	//dirs.push_back(planet2->orbitDir);
	//time += DELTA_TIME;
	//if (time > 5)
	//{
	//	Test();
	//}

}

void PlanetScene::PreRender()
{
}

void PlanetScene::Render()
{
	for (auto& i : planets)
	{
		i->Render();
	}
}

void PlanetScene::PostRender()
{
}

void PlanetScene::CreateRandomOrbit(Planet* planet, float length)
{
	Vector3 vec;
	do
	{
		vec = Vector3(rand() % 10 - 5, rand() % 10 - 5, rand() % 10 - 5).GetNormalized();
	} while (vec.Length()== 0);
	
	vec.x *= length;
	vec.y *= length;
	vec.z *= length;

	planet->SetInitialTranslation(vec);
	planet->orbitSpeed = rand() % 5 + 1;
	int num = rand() % 3;
	switch (num)
	{
	case 0:
		planet->rotationSpeed.x = rand() % 10;
		break;
	case 1:
		planet->rotationSpeed.y = rand() % 10;

		break;
	case 2:
		planet->rotationSpeed.z = rand() % 10;

		break;

	default:
		break;
	}

}

