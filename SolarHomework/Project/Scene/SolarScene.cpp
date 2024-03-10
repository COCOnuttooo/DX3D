#include "Framework.h"
#include "SolarScene.h"
SolarScene::SolarScene()
{
	//background = new SolarBackground;
	background = new ReverseSphere;
	background->GetMaterial()->SetDiffuseMap(L"SolarSystem/Universe.jpg");
	background->scale = Vector3(500, 500, 500);

}

SolarScene::~SolarScene()
{
	delete background;
	delete disc;
	for (auto& i : planets)
	{
		delete i;
	}
	planets.clear();
}

void SolarScene::Update()
{
	//for (Planet* i : planets)
	//	i->Update();
	for (int i = 0; i < planets.size(); i++)
	{
		//if (i==10)
		//{
		//	planets[i]->scale;
		//	planets[i]->translation;
		//	planets[i]->orbitSpeed;
		//}
		planets[i]->Update();
	}
	//}
	disc->Update();
	background->Update();
	background->rotation.y += DELTA_TIME * 0.02;
	MouseEvent();
}

void SolarScene::PreRender()
{
}

void SolarScene::Render()
{
	for (Planet* i : planets)
		i->Render();
	background->Render();
	disc->Render();
	//for (int i = 0; i < planets.size(); i++)
	//{

	//	//if (i== 0 || i == 10 || i==9 || i == 8 ||i == 7 || i == 6)
	//	//{
	//	//	continue;
	//	//}
	//	planets[i]->Render();
	//}

}

void SolarScene::PostRender()
{
	Debug();
	for (auto& i : planets)
	{
		i->Description();
	}
}

void SolarScene::CreateRandomOrbit(Planet* planet, float length)
{
	Vector3 vec;
	do
	{
		vec = Vector3(rand() % 10 - 5, rand() % 10 - 5, rand() % 10 - 5).GetNormalized();
	} while (vec.Length() == 0);
	vec.x *= length;
	vec.y *= length;
	vec.z *= length;
	if (vec.Length()==0)
	{
		return;
	}

	planet->orbitSpeed =2;
	planet->SetInitialTranslation(vec);
	planet->rotationSpeed.y = rand() % 10 +1;

}

void SolarScene::CreateOrbit(Planet* planet, float length, Vector3 orbitVec)
{
	Vector3 vec;
	do
	{
		vec = Vector3::Cross(Vector3(rand()%3-1, rand() % 3 - 1, rand() % 3 - 1), orbitVec).GetNormalized() * length;
	} while (vec.Length() == 0);
	planet->translation = vec;
	float test = Vector3::Dot(vec, orbitVec);
	planet->orbitSpeed = 1;
	planet->SetOrbit(orbitVec);
	planet->rotationSpeed.y = rand() % 10;

}

void SolarScene::Initialize()
{
	wstring names[12] = { L"sunmap", L"mercurymap", L"venusmap",L"earthmap",L"marsmap",L"jupitermap",L"saturnmap",L"uranusmap",L"neptunemap",L"plutomap", L"moonmap" , L"saturnringcolor" };
	string names2[12] = { "Sun", "Mercury", "Venus","Earth","Mars","Jupiter","Saturn","Uranus","Neptune","Pluto", "Moon" , "Saturnringcolor"};

	float volumeScale[11] =     { 2,0.38, 0.95, 1  ,0.53, 11, 9, 4,4, 0.18, 0.27 };
	float lengthScale[10] =     {  0.39,0.72,1,1.52,5.2,9.54,19.19, 30.7, 39, .48};
	float orbitSpeedScale[10] = { 0.24, 0.62, 1 , 1.88 , 11.86 , 29.46 ,84 ,164.8 ,248 ,0.3 };
	Vector3 orbitVec[10] = { Vector3(0.0006,1,0),Vector3(0.0454,0.999,0),Vector3(0.3987,0.9171,0),Vector3(0.4256,0.9049,0),Vector3(0.0546,9985,0),Vector3(0.4498,0.8931,0),Vector3(-0.1352,0.9908,0),Vector3(0.4744,0.8803,0),Vector3(-0.5377,0.8431,0) ,Vector3(0.1163,9932,0) };
	for (int i = 0; i < 11; i++)
	{
		wstring name = L"SolarSystem/" + names[i] + L".jpg";
		planets.push_back(new Planet);
		planets[i]->SetDiffuseMap(name);
		planets[i]->scale = Vector3(volumeScale[i], volumeScale[i], volumeScale[i]) ;
		planets[i]->SetName(names2[i]);
	}
	for (UINT i = 1; i < 10; i++)
	{
		planets[i]->SetParent(planets[0]);
		CreateOrbit(planets[i], lengthScale[i-1] * 10, orbitVec[i-1]);
		planets[i]->SetOrbitSpeedScale(orbitSpeedScale[i - 1]);
	}
	
	planets[10]->SetParent(planets[3]);
	CreateOrbit(planets[10], lengthScale[9] * 10, orbitVec[9]);
	planets[10]->SetOrbitSpeedScale(orbitSpeedScale[9]);

	planets[10]->scale;
	planets[10]->translation;

	//planets.push_back(new Planet);
	//wstring name = L"SolarSystem/" + names[11] + L".jpg";
	//planets[11]->SetDiffuseMap(name);
	//planets[11]->scale = Vector3(volumeScale[6] * 1.5, 0, volumeScale[6] * 1.5);
	//planets[11]->SetParent(planets[6]);
	//planets[11]->rotationSpeed.y = 10;

	disc = new Disc(0, 2, 50);
	disc->GetMaterial()->SetDiffuseMap(L"SolarSystem/saturnringcolor.jpg");
	disc->scale.x = planets[6]->scale.x * 0.2;
	disc->scale.y = planets[6]->scale.x * 0.2;
	disc->rotation.x = XM_PIDIV2;
	disc->SetParent(planets[6]);
	//XMFLOAT4X4 fWorld;

	//XMStoreFloat4x4(&fWorld, planets[10]->TestGetWorld());
	//Vector3 lightDir = Vector3(fWorld._41, fWorld._42, fWorld._43);

	//return;
}

void SolarScene::Debug()
{
	ImGui::Text("Mouse Pos : %.2f, %.2f", mouseNDCtest.x, mouseNDCtest.y);
	ImGui::Text("Sun Pos : %.2f, %.2f", testB, testC);

	if (ImGui::TreeNode("Solar System"))
	{
		
		if (ImGui::DragFloat("Orbit Speed",&speed,0.1f,0.0f, 5.0f))
		{
			for (auto& i : planets)
			{
				i->SetSpeedScale(speed);
			}
		}
		ImGui::TreePop();
	}
}

void SolarScene::MouseEvent()
{

	XMFLOAT2 mouseNDC;
	mouseNDC.x = (mousePos.x / WIN_WIDTH) * 2.0f - 1.0f;
	mouseNDC.y = 1.0f - (mousePos.y / WIN_HEIGHT) * 2.0f;
	mouseNDCtest = mouseNDC;
	// NDC에서 월드 좌표로 변환
	XMVECTOR nearPointNDC = XMVectorSet(mouseNDC.x, mouseNDC.y, 0.0f, 1.0f);
	XMVECTOR farPointNDC = XMVectorSet(mouseNDC.x, mouseNDC.y, 1.0f, 1.0f);

	XMMATRIX projMatrix = ENVIRONMENT->GetProjMatrix(); // 프로젝션 매트릭스
	XMMATRIX viewMatrix = ENVIRONMENT->GetCamera()->GetviewMatrix(); // 뷰 매트릭스
	XMMATRIX invProjMatrix = XMMatrixInverse(nullptr, projMatrix);
	XMMATRIX invViewMatrix = XMMatrixInverse(nullptr, viewMatrix);

	XMVECTOR nearPointWorld = XMVector3TransformCoord(nearPointNDC, invProjMatrix);
	nearPointWorld = XMVector3TransformCoord(nearPointWorld, invViewMatrix);

	XMVECTOR farPointWorld = XMVector3TransformCoord(farPointNDC, invProjMatrix);
	farPointWorld = XMVector3TransformCoord(farPointWorld, invViewMatrix);

	// 레이 생성
	XMVECTOR rayOrigin = nearPointWorld;
	XMVECTOR rayDirection = XMVector3Normalize(farPointWorld - nearPointWorld);
	int planetNum = 0;
	//bool isClicked = false;
	for (auto& planet : planets)
	{

		XMVECTOR planetCenter = XMVector3TransformCoord(XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), planet->TestGetWorld());

		// 플래닛의 실제 반지름 계산
		float planetRadius = 1.0f * planet->scale.x;

		// 레이와 플래닛 중심 사이의 최소 거리 계산
		XMVECTOR m = rayOrigin - planetCenter;
		float b = XMVectorGetX(XMVector3Dot(m, rayDirection));
		float c = XMVectorGetX(XMVector3Dot(m, m)) - planetRadius * planetRadius;
		if (planetNum == 5)
		{
			testB = b;
			testC = c;
		}
		planetNum++;

		// 충돌 여부 확인
		float discr = b * b - c;
		if (c <= 0.0f || b <= 0.0f && discr > 0.0f)
		{
			if (!isClicked)
			{
				planet->isTarget = true;
			}
			if (KEYBOARD->Down(VK_LBUTTON))
			{
				if (planetTest == planet)
				{
					planetTest;
					planet->isWire = !planet->isWire;
				}

				if (ENVIRONMENT->GetCamera()->GetParent() == nullptr)
				{
					planets[0];
					ENVIRONMENT->GetCamera()->translation = Vector3(0, 0, -planet->scale.x * 3);
					ENVIRONMENT->GetCamera()->rotation = Vector3(0, 0, 0);
					ENVIRONMENT->GetCamera()->SetParent(planet);
					planetTest = planet;

					planet->isTooltip = true;
				}
				isClicked = true;
				break;
			}
		}
		else
			planet->isTarget = false;


		isClicked = false;



	}
	if (!isClicked)
	{
		if (KEYBOARD->Down(VK_LBUTTON))
		{
			if (ENVIRONMENT->GetCamera()->GetParent() != nullptr)
			{
				ENVIRONMENT->GetCamera()->SetParent(nullptr);
				planetTest = nullptr;
				for (auto& i : planets)
				{
					i->isTooltip = false;
					i->isWire = false;
				}
			}
		}
	}
}
