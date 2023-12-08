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

void Material::SetShader()
{
	vertexShader->SetShader();
	 pixelShader->SetShader();
}
