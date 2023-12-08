#pragma once
class Material
{
public:
	Material(wstring file);
	~Material();

	void SetShader();
	void CreateShader(wstring file);
private:
	VertexShader* vertexShader;
	PixelShader*   pixelShader;
};

