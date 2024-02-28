#include "Framework.h"
#include "TargetSphere.h"
TargetSphere::TargetSphere()
{
	colliderBody = new ColliderSphere();
	texture = new Sphere();
	colliderBody->SetParent(this);
	texture->SetParent(this);
	wstring color;
	int colorNum = rand() % names.size();
	color = names[colorNum];
	texture->GetMaterial()->SetDiffuseMap(L"Solid/"  + color);
	texture->GetMaterial()->SetNormalMap(L"Solid/White.png");
	//texture->GetMaterial()->SetShader(L"01_Texture");
}

TargetSphere::~TargetSphere()
{
	delete texture;
}

void TargetSphere::Update()
{
	Target::Update();
	if (CheckAimed())
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			isActive = false;
			if (Event!= nullptr)
			{
				Event(score);
			}
		}
	}
	colliderBody->Update();
	texture->Update();
}

void TargetSphere::Render()
{
	if (isActive)
	{
		texture->Render();
	}
}

void TargetSphere::Debug()
{
	texture->GetMaterial()->Debug();
	colliderBody->Debug();
}

bool TargetSphere::CheckAimed()
{
	Ray ray = CAMERA->ScreenPointToRay(mousePos);
	HitResult result;
	if (colliderBody->Collision(ray,&result))
	{
		texture->GetMaterial()->GetBuffer()->data.emissive = Vector4(1, 0, 0, 1);
		return true;
	}
	else
		texture->GetMaterial()->GetBuffer()->data.emissive = Vector4(0, 0, 0, 1);
	return false;

}

void TargetSphere::Respawn(float lifeTime, Vector3 pos, float size)
{
	if (isActive)
	{
		return;
	}
	wstring color;

	int colorNum = rand() % names.size();
	color = names[colorNum];
	texture->GetMaterial()->SetDiffuseMap(L"Solid/" + color);
	Target::Respawn(lifeTime, pos);
	this->scale = Vector3(size, size, size);
	score = (baseScore / size) / lifeTime;
}
