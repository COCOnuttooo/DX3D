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
	void SetNormalMap(wstring file);

	void Debug();

	void SelectMap(Texture** texture, string mapType, wstring clearFile);
private:
	VertexShader* vertexShader;
	PixelShader*   pixelShader;

	
	Texture* diffuseMap = nullptr;
	Texture* specularMap = nullptr;
	Texture* normalMap = nullptr;
	string name;
	static UINT index;
};

