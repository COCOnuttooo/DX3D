#pragma once

struct MatrixBuffer : public ConstBuffer<Matrix>
{
	
	MatrixBuffer()
		:ConstBuffer(matrix)
	{
		matrix = XMMatrixIdentity();
	}

	void SetData(Matrix value)
	{
		matrix = XMMatrixTranspose(value);
	}
	Matrix matrix;
};
struct LightData
{
	Vector3 direction = Vector3(0, -1, 0);
	float padding;
};
struct LightBuffer : public ConstBuffer<LightData>
{
	LightBuffer()
		:ConstBuffer(data)
	{
	}
	LightData data;


};