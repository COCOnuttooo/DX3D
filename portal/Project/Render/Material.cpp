#include "Framework.h"
#include "Material.h"
UINT Material::index = 0;
Material::Material(wstring file)
{
	CreateShader(file);
	name = "Material_" + to_string(index++);

}

Material::~Material()
{
}

void Material::CreateShader(wstring file)
{
	vertexShader = Shader::AddVS(file);
	 pixelShader = Shader::AddPS(file);
}

void Material::SetDiffuseMap(wstring file)
{
	diffuseMap = Texture::Add(file);
}

void Material::SetDiffuseMap(ID3D11Texture2D** texture, wstring key)
{
	diffuseMap = Texture::Add(texture, key);
}

void Material::SetSpecularMap(wstring file)
{
	specularMap = Texture::Add(file);
}

void Material::SetNormalMap(wstring file)
{
	normalMap = Texture::Add(file);
}

void Material::Debug()
{
	if (ImGui::TreeNode(name.c_str()))
	{
		SelectMap(&diffuseMap, "DiffuseMap", L"Solid/White.png");
		SelectMap(&specularMap, "SpecularMap", L"Solid/Black.png");
		SelectMap(&normalMap, "NormalMap", L"Solid/White.png");
		//ImTextureID textureID;
		//if (diffuseMap != nullptr)
		//{

		//	textureID = diffuseMap->GetSRV();
		//	ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.952f, 1), "DiffuseMap");
		//	if (ImGui::ImageButton(textureID, ImVec2(50,50)))
		//		DIALOG->OpenDialog("DiffuseMap", "DiffuseMap", ".png,.jpg, .tga,.dds,.TGA,.JPG,.PNG,.DDS", "_Texture/");
		//}
		//else
		//{
		//	textureID = NOIMAGE->GetSRV();
		//	ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.952f, 1), "DiffuseMap");
		//	if (ImGui::ImageButton(textureID, ImVec2(50, 50)))
		//		DIALOG->OpenDialog("DiffuseMap", "DiffuseMap", ".png,.jpg, .tga,.dds,.TGA,.JPG,.PNG,.DDS", "_Texture/");
		//}

		//if (specularMap != nullptr)
		//{

		//	textureID = specularMap->GetSRV();
		//	ImGui::TextColored(ImVec4(0.0f, 0.f, 0.952f, 1), "SpecularMap");

		//	if (ImGui::ImageButton(textureID, ImVec2(50, 50)))
		//		DIALOG->OpenDialog("SpecularMap", "SpecularMap", ".png,.jpg, .tga,.dds,.TGA,.JPG,.PNG,.DDS", "_Texture/");
		//}
		//else
		//{
		//	textureID = NOIMAGE->GetSRV();
		//	ImGui::TextColored(ImVec4(0.f, 0.f, 0.952f, 1), "SpecularMap");

		//	if (ImGui::ImageButton(textureID, ImVec2(50, 50)))
		//		DIALOG->OpenDialog("SpecularMap", "SpecularMap", ".png,.jpg, .tga,.dds,.TGA,.JPG,.PNG,.DDS", "_Texture/");
		//}

		//if (normalMap != nullptr)
		//{

		//	textureID = normalMap->GetSRV();
		//	ImGui::TextColored(ImVec4(0.f, 0.f, 0.952f, 1), "NormalMap");

		//	if (ImGui::ImageButton(textureID, ImVec2(50, 50)))
		//		DIALOG->OpenDialog("NormalMap", "NormalMap", ".png,.jpg, .tga,.dds,.TGA,.JPG,.PNG,.DDS", "_Texture/");
		//}
		//else
		//{
		//	textureID = NOIMAGE->GetSRV();
		//	ImGui::TextColored(ImVec4(0.f,0.f,0.f,1),"NormalMap");

		//	if (ImGui::ImageButton(textureID, ImVec2(50, 50)))
		//		DIALOG->OpenDialog("NormalMap", "NormalMap", ".png,.jpg, .tga,.dds,.TGA,.JPG,.PNG,.DDS", "_Texture/");

		//}
		ImGui::TreePop();
	}
	if (DIALOG->Display("DiffuseMap",32, ImVec2(300,100))|| DIALOG->Display("SpecularMap", 32, ImVec2(300, 100)) || DIALOG->Display("NormalMap",32,ImVec2(300,100)))
	{
		if (DIALOG->IsOk())
		{
			string path = DIALOG->GetFilePathName();
			path = path.substr(projectDir.length() + 1, path.length());

			if (DIALOG->GetOpenedKey() == "DiffuseMap")
				SetDiffuseMap(ToWString(path));
			if (DIALOG->GetOpenedKey() == "SpecularMap")
				SetSpecularMap(ToWString(path));
			if (DIALOG->GetOpenedKey() == "NormalMap")
				SetNormalMap(ToWString(path));
		}
		DIALOG->Close();
	}
}

void Material::SelectMap(Texture** texture, string mapType, wstring clearFile)
{
	ImTextureID textureID = Texture::Add(clearFile, ToWString(mapType) + clearFile)->GetSRV();
	if (*texture)
		textureID = (*texture)->GetSRV();


	ImGui::TextColored(ImVec4(0.611f, 0.862f, 0.952f, 1.0f), mapType.c_str());
	if (ImGui::ImageButton(textureID, ImVec2(50,50)))
		DIALOG->OpenDialog(mapType, mapType, ".png,.jpg, .tga,.dds,.TGA,.JPG,.PNG,.DDS", "_Texture/");
	ImGui::SameLine();
	textureID = Texture::Add(L"Miscellaneous/X_Image.png", ToWString(mapType) + L"X_Image")->GetSRV();
	if (ImGui::ImageButton(textureID,ImVec2(20,20)))
		*texture = Texture::Add(clearFile, ToWString(mapType) + clearFile);
}

void Material::Set()
{
	vertexShader->SetShader();
	 pixelShader->SetShader();
	 if (diffuseMap != nullptr)
		 diffuseMap->PSSetShaderResources(0);
	 if (specularMap != nullptr)
		 specularMap->PSSetShaderResources(1);
	 if (normalMap != nullptr)
		 normalMap->PSSetShaderResources(2);

}