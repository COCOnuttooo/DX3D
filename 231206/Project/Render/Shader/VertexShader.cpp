#include "Framework.h"
#include "VertexShader.h"
VertexShader::VertexShader(wstring file)
{
	DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;


	D3DCompileFromFile
	(
		file.c_str(),
		nullptr, nullptr,
		"VS",
		"vs_5_0",
		flags,
		0,
		&blob,
		nullptr
	);

	DEVICE->CreateVertexShader
	(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&vertexShader
	);

	CreateInputLayout();


}

VertexShader::~VertexShader()
{
	vertexShader->Release();
	inputLayout->Release();
}

void VertexShader::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC desc[2] = {};

	desc[0].SemanticName = "POSITION";
	desc[0].SemanticIndex = 0;
	desc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	desc[0].InputSlot = 0;
	desc[0].AlignedByteOffset = 0;
	desc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	desc[0].InstanceDataStepRate = 0;

	desc[1].SemanticName = "COLOR";
	desc[1].SemanticIndex = 0;
	desc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc[1].InputSlot = 0;
	desc[1].AlignedByteOffset = 12;
	desc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	desc[1].InstanceDataStepRate = 0;

	UINT layoutSize = ARRAYSIZE(desc);

	DEVICE->CreateInputLayout
	(
		desc,
		layoutSize,
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&inputLayout
	);
}

void VertexShader::SetShader()
{
	DC->IASetInputLayout(inputLayout);
	DC->VSSetShader(vertexShader, nullptr, 0);
}

