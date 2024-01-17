#pragma once

class Material
{
public:
	Material();
	Material(wstring file);
	~Material();

	void Set();

	void SetShader(wstring file);

	void SetDiffuseMap(wstring file);
	void SetSpecularMap(wstring file);
	void SetNormalMap(wstring file);

	void Debug();

	void SelectMap(Texture** texture, string mapType, wstring clearFile);

	void Save(wstring file);
	void Load(wstring file);

	void SaveDialog();
	void LoadDialog();

	void SetName(string name) { this->name = name; }

	MaterialBuffer* GetBuffer() { return buffer; }

	string GetName() { return name; }
private:
	VertexShader* vertexShader;
	 PixelShader*  pixelShader;

	 Texture*  diffuseMap = nullptr;
	 Texture* specularMap = nullptr;
	 Texture*   normalMap = nullptr;

	 string name;
	 static UINT index;

	 MaterialBuffer* buffer;
};
