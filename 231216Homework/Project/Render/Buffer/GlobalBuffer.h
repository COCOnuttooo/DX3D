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