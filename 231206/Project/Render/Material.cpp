#include "Framework.h"
#include "Material.h"
Material::Material(wstring file)
{
	CreateShader(file);
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

void Material::Set()
{
	vertexShader->SetShader();
	 pixelShader->SetShader();
	 if (diffuseMap != nullptr)
		 diffuseMap->PSSetShaderResources(0);
}
