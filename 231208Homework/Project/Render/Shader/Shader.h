#pragma once
class Shader
{
protected:
	virtual ~Shader();

public:

	virtual void SetShader() = 0;

	static void Delete();

	static class VertexShader* AddVS(wstring file);
	static class PixelShader*  AddPS(wstring file);

protected:
	ID3DBlob* blob = nullptr;

	static map<wstring, Shader*> shaders;
};

