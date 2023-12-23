#pragma once
class Material
{
public:
	Material(wstring file);
	~Material();

	void Set();
	void CreateShader(wstring file);

	void SetDiffuseMap(wstring file);
	void SetSpecularMap(wstring file);
private:
	VertexShader* vertexShader;
	PixelShader*   pixelShader;

	Texture* diffuseMap = nullptr;
	Texture* specularMap = nullptr;
	Texture* normalMap = nullptr;
};

