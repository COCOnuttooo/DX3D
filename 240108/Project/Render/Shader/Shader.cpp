#include "Framework.h"
#include "Shader.h"

map<wstring, Shader*> Shader::shaders = {};

Shader::~Shader()
{
	blob->Release();
}

void Shader::Delete()
{
	for (pair<wstring, Shader*> shader : shaders)
		delete shader.second;

	shaders.clear();
}

VertexShader* Shader::AddVS(wstring file)
{
	wstring key = L"VS" + file;

	file = L"_Shader/" + file + L".hlsl";

	assert(PathFileExists(file.c_str()));

	if (shaders.count(key) > 0)
		return (VertexShader*)shaders[key];

	shaders.emplace(key, new VertexShader(file));

	return (VertexShader*)shaders[key];
}

PixelShader* Shader::AddPS(wstring file)
{
	wstring key = L"PS" + file;

	file = L"_Shader/" + file + L".hlsl";

	assert(PathFileExists(file.c_str()));

	if (shaders.count(key) > 0)
		return (PixelShader*)shaders[key];

	shaders.emplace(key, new PixelShader(file));

	return (PixelShader*)shaders[key];
}

ComputeShader* Shader::AddCS(wstring file)
{
	wstring key = L"CS" + file;

	file = L"_Shader/" + file + L".hlsl";

	assert(PathFileExists(file.c_str()));

	if (shaders.count(key) > 0)
		return (ComputeShader*)shaders[key];

	shaders.emplace(key, new ComputeShader(file));

	return (ComputeShader*)shaders[key];
}
