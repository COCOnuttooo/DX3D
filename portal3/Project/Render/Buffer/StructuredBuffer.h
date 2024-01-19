#pragma once
class StructuredBuffer
{
public:
	StructuredBuffer
	(
		void* inputData, 
		UINT inputStride, 
		UINT inputCount, 
		UINT outputStride, 
		UINT outputCount
	);
	~StructuredBuffer();

	void Copy(void* data, UINT size);
	ID3D11Buffer* GetInput() { return input; }
	void UpdateInput(void* data);
private:
	void CreateInput();
	void CreateSRV();
	void CreateOutput();
	void CreateUAV(); //Unordered Access View
	void CreateResult();

private:
	ID3D11Buffer* input;
	ID3D11ShaderResourceView* srv;

	ID3D11Buffer* output;
	ID3D11UnorderedAccessView* uav;

	ID3D11Buffer* result;

	void* inputData;

	UINT inputStride, inputCount;
	UINT outputStride, outputCount;
};

