#include "Framework.h"
#include "Material.h"

UINT Material::index = 0;

Material::Material()
{
	name = "Material_" + to_string(index++);
	buffer = new MaterialBuffer;
}

Material::Material(wstring file)
{
	SetShader(file);
	name = "Material_" + to_string(index++);
	buffer = new MaterialBuffer;

}

Material::~Material()
{
	delete buffer;

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

void Material::SetShader(wstring file)
{
	vertexShader = Shader::AddVS(file);
	 pixelShader = Shader::AddPS(file);
}

void Material::SetDiffuseMap(wstring file)
{
	diffuseMap = Texture::Add(file);

	buffer->data.hasDiffuseMap = true;
}

void Material::SetSpecularMap(wstring file)
{
	specularMap = Texture::Add(file);

	buffer->data.hasSpecularMap = true;

}

void Material::SetNormalMap(wstring file)
{
	normalMap = Texture::Add(file);

	buffer->data.hasNormalMap = true;
}

void Material::Debug()
{
	if (ImGui::TreeNode(name.c_str()))
	{
		SelectMap(&diffuseMap,  "DiffuseMap",  L"Solid/White.png");
		SelectMap(&specularMap, "SpecularMap", L"Solid/Black.png");
		SelectMap(&normalMap,   "NormalMap",   L"Solid/White.png");

		SaveDialog();
		LoadDialog();

		ImGui::TreePop();
	}

	if (DIALOG->Display("DiffuseMap", 32, ImVec2(300, 100)) || DIALOG->Display("SpecularMap", 32, ImVec2(300, 100)) || DIALOG->Display("NormalMap", 32, ImVec2(300, 100)))
	{
		if (DIALOG->IsOk())
		{
			string path = DIALOG->GetFilePathName();

			path = path.substr(projectDir.length() + 1, path.length());

			if (DIALOG->GetOpenedKey() == "DiffuseMap")
				SetDiffuseMap(ToWString(path));
			else if (DIALOG->GetOpenedKey() == "SpecularMap")
				SetSpecularMap(ToWString(path));
			else if (DIALOG->GetOpenedKey() == "NormalMap")
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

	if (ImGui::ImageButton(textureID, ImVec2(50, 50)))
	{
		DIALOG->OpenDialog(mapType, mapType, ".png,.jpg,.tga,.dds,.TGA,.PNG,.JPG,.DDS", "_Texture/");
	}

	ImGui::SameLine();

	textureID = Texture::Add(L"Miscellaneous/X_Image.png", ToWString(mapType) + L"X_Image")->GetSRV();

	if (ImGui::ImageButton(textureID, ImVec2(20, 20)))
		*texture = Texture::Add(clearFile, ToWString(mapType) + clearFile);
}

void Material::Save(wstring file)
{
	BinaryWriter data(file);

	data.WriteData(name);

	if (vertexShader)
		data.WriteData(vertexShader->GetPath());
	else
		data.WriteData("");

	if (pixelShader)
		data.WriteData(pixelShader->GetPath());
	else
		data.WriteData("");


	if (diffuseMap)
		data.WriteData(diffuseMap->GetPath());
	else
		data.WriteData("");

	if (specularMap)
		data.WriteData(specularMap->GetPath());
	else
		data.WriteData("");

	if (normalMap)
		data.WriteData(normalMap->GetPath());
	else
		data.WriteData("");


	data.WriteData(buffer->data.diffuse);
	data.WriteData(buffer->data.specular);
	data.WriteData(buffer->data.ambient);
	data.WriteData(buffer->data.emissive);
	data.WriteData(buffer->data.shininess);
}

void Material::Load(wstring file)
{
	BinaryReader data(file);

	name = data.ReadString();

	wstring str;

	str = data.ReadWString();

	if (str != L"")
		vertexShader = Shader::AddVS(str);


	str = data.ReadWString();

	if (str != L"")
		pixelShader = Shader::AddPS(str);

	str = data.ReadWString();

	if (str != L"")
		SetDiffuseMap(str);

	str = data.ReadWString();

	if (str != L"")
		SetSpecularMap(str);

	str = data.ReadWString();

	if (str != L"")
		SetNormalMap(str);

	buffer->data.diffuse   = data.ReadVector4();
	buffer->data.specular  = data.ReadVector4();
	buffer->data.ambient   = data.ReadVector4();
	buffer->data.emissive  = data.ReadVector4();
	buffer->data.shininess = data.ReadFloat();
}

void Material::SaveDialog()
{
	if (ImGui::Button("SaveMaterial"))
		DIALOG->OpenDialog("SaveMaterial", "SaveMaterial", ".mat", "_TextData/");

	if (DIALOG->Display("SaveMaterial", 32, ImVec2(300, 100)))
	{
		if (DIALOG->IsOk())
		{
			string file = DIALOG->GetFilePathName();

			file = file.substr(projectDir.size() + 1, file.size());

			Save(ToWString(file));
		}

		DIALOG->Close();
	}
}

void Material::LoadDialog()
{
	if (ImGui::Button("LoadMaterial"))
		DIALOG->OpenDialog("LoadMaterial", "LoadMaterial", ".mat", "_TextData/");

	if (DIALOG->Display("LoadMaterial", 32, ImVec2(300, 100)))
	{
		if (DIALOG->IsOk())
		{
			string file = DIALOG->GetFilePathName();

			file = file.substr(projectDir.size() + 1, file.size());

			Load(ToWString(file));
		}

		DIALOG->Close();
	}
}
