#pragma once
class PixelShader : public Shader
{
	friend class Shader;
private:
	PixelShader(wstring file);
	~PixelShader();
public:
	// Shader��(��) ���� ��ӵ�
	void SetShader() override;

private:
	ID3D11PixelShader* pixelShader;
};


