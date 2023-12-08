#pragma once
class VertexShader : public Shader
{
	friend class Shader;

private:

	VertexShader(wstring file);
	~VertexShader();

public:
	void CreateInputLayout();
	// Shader��(��) ���� ��ӵ�
	void SetShader() override;

private:

	ID3D11VertexShader* vertexShader;
	ID3D11InputLayout* inputLayout;

};

