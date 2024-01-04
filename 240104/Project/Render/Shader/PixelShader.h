#pragma once
class PixelShader : public Shader
{
	friend class Shader;
private:
	PixelShader(wstring file);
	~PixelShader();
public:
	// Shader을(를) 통해 상속됨
	void SetShader() override;

private:
	ID3D11PixelShader* pixelShader;
};


