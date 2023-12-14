#pragma once
class Material
{
public:
	Material(wstring file);
	~Material();

	void Set();
	void CreateShader(wstring file);

	void SetDiffuseMap(wstring file);
private:
	VertexShader* vertexShader;
	PixelShader*   pixelShader;

	Texture* diffuseMap = nullptr;
};

