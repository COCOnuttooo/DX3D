#include "Framework.h"
#include "TargetCube.h"

TargetCube::TargetCube()
{
	colliderBody = new ColliderBox();
	texture = new TextureCube();
	colliderBody->SetParent(this);
	texture->SetParent(this);
	wstring color;
	int colorNum = rand() % names.size();
	color = names[colorNum];
	texture->SetDiffuseMap(L"Solid/" + color);
	texture->SetNormalMap(L"Solid/White.png");
	texture->SetShader(L"05_NormalMapping");
	//texture->SetEmissive(Vector4(1, 0, 0, 1));
}

TargetCube::~TargetCube()
{
	delete texture;
}

void TargetCube::Update()
{
	Target::Update();
	if (CheckAimed())
	{
		if (KEY_DOWN(VK_LBUTTON))
		{
			isActive = false;
			if (Event != nullptr)
			{
				Event(score);
			}
		}
	}
	colliderBody->Update();
	texture->Update();
}

void TargetCube::Render()
{
	if (isActive)
	{
		texture->Render();
	}
}

void TargetCube::Respawn(float lifeTime, Vector3 pos, float size)
{
	wstring color;

	int colorNum = rand() % names.size();
	color = names[colorNum];
	texture->SetDiffuseMap(L"Solid/" + color);

	Target::Respawn(lifeTime, pos);
	this->scale = Vector3(size, size, size);
	score = (baseScore / size) / lifeTime;
}

bool TargetCube::CheckAimed()
{
	if (!isActive)
	{
		return false;
	}
	Ray ray = CAMERA->ScreenPointToRay(mousePos);
	HitResult result;
	if (colliderBody->Collision(ray, &result))
	{
		texture->SetEmissive(Vector4(1, 0, 0, 1));
		return true;
	}
	else
		texture->SetEmissive(Vector4(0, 0, 0, 1));

	return false;

}
