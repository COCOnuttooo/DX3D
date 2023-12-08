#pragma once
class VertexShader : public Shader
{
	friend class Shader;

private:

	VertexShader(wstring file);
	~VertexShader();

public:
	void CreateInputLayout();
	// Shader을(를) 통해 상속됨
	void SetShader() override;

private:

	ID3D11VertexShader* vertexShader;
	ID3D11InputLayout* inputLayout;

};

