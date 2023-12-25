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
		s = u8" �¾���� �߽ɿ� ��ġ�ϸ�, �ַ� ���ҿ� ������� ������ �Ŵ��� �׼��Դϴ�. �¾��� �������� �� ���� ���� �µ��� �����ϴ� �ֵ� �����̸�, �¾���� ��� õü�� ��� �߷��� ������ ��Ĩ�ϴ�.";
		break;
	case 1:
		s = u8"�¾翡 ���� ����� �༺����, �ſ� ���� ��⸦ ������ ������ �ش����� �µ� ��ȭ�� �����մϴ�. ������ ǥ���� ũ�����Ϳ� �ް� ������ ����� ������ �ֽ��ϴ�.";
		break;
	case 2:
		s = u8"������ ũ��� ������ ���������, �ſ� �β��� �̻�ȭź�� ���� ���� ǥ�� �µ��� ������ �־� �½� ȿ���� �ش����� ���� �������ϴ�. �ݼ��� �������� ���⿡ ���� ���� õü �� �ϳ��Դϴ�.";
		break;
	case 3:
		s = u8"����ü�� �����ϴ� ������ �༺���� �˷��� ������, ���ҿ� ��ҷ� ������ ��⸦ ������ �ֽ��ϴ�. ������ �پ��� ���Ŀ� ������ ������ �ֽ��ϴ�.";
		break;
	case 4:
		s = u8"'���� �༺'�̶�� �Ҹ���, ���� �̻�ȭź�� ���� ������ ���� ���� ���� ��ϴ�. ȭ������ �ֱٱ����� ���� ���簡 ������ ū ������ �ް� �ֽ��ϴ�.";
		break;
	case 5:
		s = u8"�¾�迡�� ���� ū �༺����, �ַ� ������ �����Ǿ� �ֽ��ϴ�. ū ũ��� ������ �ڱ����� ������ ������, ������ �������̶�� ��ǳ�� �����մϴ�.";
		break;
	case 6:
		s = u8"�Ƹ��ٿ� ���� �ý������� ������ ���� �༺�Դϴ�. �伺�� ������ ������ �ϼ� �������� �̷���� ������, ���� ���� �Ŵ����� �ֽ��ϴ�.";
		break;
	case 7:
		s = u8"Ǫ�� ���� ��� ���� �༺����, ��ź ��� ������ �� ���� ��ϴ�. õ�ռ��� �¾�� �༺ �� �����ϰ� ������ ������ �����մϴ�.";
		break;
	case 8:
		s = u8"�¾�迡�� �¾翡 ���� �ָ� ������ �༺����, ������ �ٶ��� ��ǳ�� Ư¡�Դϴ�. �ؿռ� ���� Ǫ�� ���� ��µ�, �̴� ��ź �����Դϴ�.";
		break;
	case 9:
		s = u8"2006�� ���������� �༺���� �з��Ǿ�����, ����� '���༺'���� �з��˴ϴ�. ���ռ��� ������ �ϼ����� �̷���� ������, �ſ� ���� ��⸦ �����ϴ�.";
		break;
	case 10:
		s = u8": ������ ������ �ڿ� ��������, ��Ⱑ ���� ǥ�鿡�� ���� ũ�����Ϳ� ���� �ֽ��ϴ�. ���� ������ ���� �������� �ֿ� �����̸�, �������� �Ÿ� ������ �������� �� �� �׻� ���� �鸸 ���Դϴ�.";
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
