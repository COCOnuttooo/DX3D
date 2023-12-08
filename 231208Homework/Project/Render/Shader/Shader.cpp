#include "Framework.h"
#include "Shader.h"
map<wstring, Shader*> Shader::shaders = {};

Shader::~Shader()
{
	blob->Release();
}

void Shader::Delete()
{
	for (pair<wstring,Shader*> shader: shaders )
		delete shader.second;
	shaders.clear();
}

VertexShader* Shader::AddVS(wstring file)
{
	wstring key = file + L"_VS";
	file = L"_Shader/" + file + L".hlsl";
	if (shaders.count(key) > 0)
		return (VertexShader*)shaders[key];
	shaders.emplace(key, new VertexShader(file));
	return (VertexShader*)shaders[key];

}

PixelShader* Shader::AddPS(wstring file)
{
	wstring key = file + L"_PS";
	file = L"_Shader/" + file + L".hlsl";
	if (shaders.count(key) > 0)
		return (PixelShader*)shaders[key];
	shaders.emplace(key, new PixelShader(file));
	return (PixelShader*)shaders[key];
}
