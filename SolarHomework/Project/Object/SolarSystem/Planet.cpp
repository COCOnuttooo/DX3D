#include "Framework.h"
#include "Planet.h"
int Planet::planetNum = 0;
Planet::Planet()
{
	sphere = new Sphere;
	sphere->SetParent(this);
	lightBuffer = new LightBuffer;
	whichNum = planetNum;
	planetNum++;
}

Planet::~Planet()
{
	delete sphere;
	delete lightBuffer;
}

void Planet::Update()
{
	//Transform::Update();
	rotation += rotationSpeed * DELTA_TIME;
	angle += DELTA_TIME * orbitSpeed * orbitSpeedScale;
	//rotation2.y += orbitSpeed.y * DELTA_TIME;
	//rotation2.x += orbitSpeed.x * DELTA_TIME;
	UpdateWorldMatrix();
	XMFLOAT4X4 fWorld;

	XMStoreFloat4x4(&fWorld, world);
	Vector3 lightDir = Vector3(fWorld._41, fWorld._42, fWorld._43);
	if (lightDir.Length() == 0)
		lightBuffer->data.padding = 0;
	else
		lightBuffer->data.padding = 1;
	lightBuffer->data.direction = lightDir;
	sphere->Update();

	
}

void Planet::UpdateWorldMatrix()
{
	Matrix S = XMMatrixScaling(scale.x, scale.y, scale.z);

	Matrix R = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
	//Matrix R2 = XMMatrixRotationRollPitchYaw(rotation2.x, rotation2.y, rotation2.z);

	Matrix T = XMMatrixTranslation(translation.x, translation.y, translation.z);


	Matrix P = XMMatrixTranslation(pivot.x, pivot.y, pivot.z);
	Matrix IP = XMMatrixInverse(nullptr, P);

	if (parent != nullptr)
	{
		Matrix R2 = XMMatrixRotationAxis(orbitDir, angle);
		world = IP * S * R * T * R2 * P;
		Matrix temp = static_cast<Planet*>(parent)->GetParentMat();
		Matrix parentWorld = XMMatrixTranslation
		(
			temp.r[3].m128_f32[0],
			temp.r[3].m128_f32[1],
			temp.r[3].m128_f32[2]
		);
		world *= parentWorld;

	}
	else
	{
		world = IP * S * R * T * P;
	}

	//if (parent != nullptr)
	//	world *= parent->world;

	XMFLOAT4X4 fWorld;

	XMStoreFloat4x4(&fWorld, world);

	right = Vector3(fWorld._11, fWorld._12, fWorld._13).GetNormalized();
	up = Vector3(fWorld._21, fWorld._22, fWorld._23).GetNormalized();
	forward = Vector3(fWorld._31, fWorld._32, fWorld._33).GetNormalized();
}

void Planet::Render()
{
	lightBuffer->SetPSBuffer(1);
	if (isWire)
		STATE->EnableWireFrame();

	sphere->Render();
	if (isWire)
		STATE->DisableWireFrame();

}

void Planet::SetInitialTranslation(Vector3 vec)
{
	translation.x = vec.x;
	translation.y = vec.y;
	translation.z = vec.z;
	if (translation.Length() <= 0)
	{
		return;
	}
	if (parent != nullptr)
	{
		do
		{
			orbitDir = -Vector3::Cross(Vector3(rand()%3-1, rand() % 3 - 1, rand() % 3 - 1), translation).GetNormalized();

		} while (orbitDir.Length()==0);
		//orbitDir = translation.GetNormalized();
		Vector3::Dot(translation, orbitDir);
	}
}

void Planet::SetOrbit(Vector3 vec)
{
	orbitDir = vec;
}

void Planet::SetDiffuseMap(wstring file)
{
	sphere->GetMaterial()->SetDiffuseMap(file);
}

void Planet::SetSpecularMap(wstring file)
{
	sphere->GetMaterial()->SetSpecularMap(file);

}

void Planet::Description()
{
	if (isTarget || isTooltip)
	{
		ImGui::BeginTooltip();
		ImGui::Text(name.c_str());
		ImGui::EndTooltip();
	}
	string s;
	switch (whichNum)
	{
	case 0:
		s = u8" 태양계의 중심에 위치하며, 주로 수소와 헬륨으로 구성된 거대한 항성입니다. 태양은 지구에서 볼 때의 밝기와 온도를 제공하는 주된 광원이며, 태양계의 모든 천체의 운동에 중력적 영향을 미칩니다.";
		break;
	case 1:
		s = u8"태양에 가장 가까운 행성으로, 매우 얇은 대기를 가지고 있으며 극단적인 온도 변화를 경험합니다. 수성의 표면은 크레이터와 달과 유사한 경관을 가지고 있습니다.";
		break;
	case 2:
		s = u8"지구와 크기와 구성이 비슷하지만, 매우 두꺼운 이산화탄소 대기와 높은 표면 온도를 가지고 있어 온실 효과의 극단적인 예로 여겨집니다. 금성은 지구에서 보기에 가장 밝은 천체 중 하나입니다.";
		break;
	case 3:
		s = u8"생명체가 존재하는 유일한 행성으로 알려져 있으며, 질소와 산소로 구성된 대기를 가지고 있습니다. 지구는 다양한 기후와 지형을 가지고 있습니다.";
		break;
	case 4:
		s = u8"'붉은 행성'이라고 불리며, 얇은 이산화탄소 대기와 먼지로 인해 붉은 색을 띕니다. 화성에는 최근까지도 물의 존재가 밝혀져 큰 관심을 받고 있습니다.";
		break;
	case 5:
		s = u8"태양계에서 가장 큰 행성으로, 주로 가스로 구성되어 있습니다. 큰 크기와 강력한 자기장을 가지고 있으며, 유명한 대적점이라는 폭풍이 존재합니다.";
		break;
	case 6:
		s = u8"아름다운 고리 시스템으로 유명한 가스 행성입니다. 토성의 고리는 얼음과 암석 조각으로 이루어져 있으며, 여러 달을 거느리고 있습니다.";
		break;
	case 7:
		s = u8"푸른 색을 띄는 가스 행성으로, 메탄 대기 때문에 이 색을 띕니다. 천왕성은 태양계 행성 중 유일하게 옆으로 누워서 공전합니다.";
		break;
	case 8:
		s = u8"태양계에서 태양에 가장 멀리 떨어진 행성으로, 강력한 바람과 폭풍이 특징입니다. 해왕성 역시 푸른 색을 띠는데, 이는 메탄 때문입니다.";
		break;
	case 9:
		s = u8"2006년 이전까지는 행성으로 분류되었으나, 현재는 '왜행성'으로 분류됩니다. 명왕성은 얼음과 암석으로 이루어져 있으며, 매우 얇은 대기를 가집니다.";
		break;
	case 10:
		s = u8": 지구의 유일한 자연 위성으로, 대기가 없고 표면에는 많은 크레이터와 산이 있습니다. 달은 지구에 대한 조석력의 주요 원인이며, 지구와의 거리 때문에 지구에서 볼 때 항상 같은 면만 보입니다.";
		break;
	case 11:
		s = u8"";
		break;
	case 12:
		s = u8"";
		break;
	default:
		break;
	}

	if (isTooltip)
	{

		ImGui::BeginTooltip();
		ImGui::Text("%s", s.c_str());
		ImGui::EndTooltip();
	}
	
}

