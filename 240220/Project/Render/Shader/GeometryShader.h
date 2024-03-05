#pragma once

class GeometryShader : public Shader
{
	friend class Shader;

	GeometryShader(wstring file);
	~GeometryShader();

public:
	void SetShader() override;

private:
	ID3D11GeometryShader* geometryShader;
};
