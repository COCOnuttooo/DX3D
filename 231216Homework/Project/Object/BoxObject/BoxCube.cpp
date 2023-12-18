#include "Framework.h"
#include "BoxCube.h"
BoxCube::BoxCube()
{
	mainBody = new Transform;
	for (int i = 0; i < 6; i++)
	{
		parts.push_back(new Quad);
		parts[i]->SetParent(mainBody);
		parts[i]->GetMaterial()->SetDiffuseMap(L"Landscape/Box.png");
		if (i < 4)
		{
			parts[i]->rotation.x = XM_PIDIV2 * i;
			
		}
		else if (i == 4)
		{
			parts[i]->rotation.y = XM_PIDIV2;
		}
		else if (i == 5)
		{
			parts[i]->rotation.y = -XM_PIDIV2;
		}
		
	}
	parts[0]->translation.z = -0.5;
	parts[1]->translation.y = 0.5;
	parts[2]->translation.z = 0.5;
	parts[3]->translation.y = -0.5;
	parts[4]->translation.x = -0.5;
	parts[5]->translation.x = 0.5;

	names.push_back(L"Landscape/Box.png");
	names.push_back(L"Landscape/Bricks.png"      ) ;
	names.push_back(L"Landscape/Bricks_normal.png");
	names.push_back(L"Landscape/Dirt.png"        ) ;
	names.push_back(L"Landscape/Wall.png"        ) ;
	boxCubeBounds.Center = mainBody->translation;
	boxCubeBounds.Extents = XMFLOAT3(mainBody->scale.x * 0.5, mainBody->scale.y * 0.5, mainBody->scale.z * 0.5);
}

BoxCube::~BoxCube()
{
	for (auto& i : parts)
	{
		delete i;
	}
}

void BoxCube::Render()
{
	for (auto& i : parts)
	{
		i->Render();
	}
}

void BoxCube::Update()
{
	mainBody->Update();
	for (auto& i : parts)
	{
		i->Update();
	}
}

void BoxCube::Debug()
{
	if (ImGui::TreeNode("BoxOption"))
	{
		ImGui::Text("MousePos : %.2f, %.2f, %.2f", (mousePos.x - WIN_WIDTH * 0.5f) / WIN_WIDTH, -(mousePos.y - WIN_HEIGHT * 0.5f)/WIN_HEIGHT, mousePos.z);
		ImGui::Text("Pos : %d, %d, %d", (int)mainBody->translation.x, (int)mainBody->translation.y, (int)mainBody->translation.z);
		ImGui::Text("Rot : %.2f, %.2f, %.2f", mainBody->rotation.x, mainBody->rotation.y, mainBody->rotation.z);
		ImGui::SliderFloat3("Rotation", (float*)&mainBody->rotation, -XM_PI * 2, XM_PI * 2);
		ImGui::SliderFloat3("Scale", (float*)&mainBody->scale, 0, 50);
		ImGui::SliderFloat3("Translation", (float*)&mainBody->translation, -50, 50);

		if (ImGui::Button("Set Default"))
		{
			mainBody->scale = { 1,1,1 };
			mainBody->rotation = { 0,0,0 };
			mainBody->translation = { 0,0,0 };

		}
		for (int i = 0; i < names.size(); i++)
		{
			void* textureId = reinterpret_cast<void*>(Texture::Add(names[i])->GetSrv());
			if (ImGui::ImageButton(textureId, ImVec2(128, 128)))
			{
				SetTexture(names[i]);
			}
			if (i%2 ==0)
			{
				ImGui::SameLine();

			}
		}
	
		ImGui::TreePop();
	}
}

void BoxCube::SetTexture(wstring file)
{
	for (auto& i : parts)
	{
		i->GetMaterial()->SetDiffuseMap(file);
	}
}

void BoxCube::MouseInteraction()
{
	Vector3 oldPos;
	if (mousePos.x < mainBody->translation.x + mainBody->scale.x * 0.5 - 0.5 * WIN_WIDTH)
	{
		if (mousePos.x> mainBody->translation.x - mainBody->scale.x *0.5 - 0.5 * WIN_WIDTH)
		{
			if (mousePos.y > mainBody->translation.y - mainBody->scale.y * 0.5 - 0.5 * WIN_HEIGHT)
			{
				if (mousePos.y < mainBody->translation.y + mainBody->scale.y * 0.5 - 0.5 * WIN_HEIGHT)
				{
					if (KEYBOARD->Press(VK_LBUTTON))
					{
						mainBody->translation.x = mousePos.x;
						mainBody->translation.y = mousePos.y;
					}
					oldPos = mousePos;
				}
			}
		}
	}
}
