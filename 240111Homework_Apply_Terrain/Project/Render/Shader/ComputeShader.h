#pragma once
class ComputeShader : public Shader
{
	friend class Shader;
private:
	ComputeShader(wstring file);
	~ComputeShader();
public:
	// Shader을(를) 통해 상속됨
	void SetShader() override;

private:
	ID3D11ComputeShader* computeShader;
};


