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

struct ViewData
{
	Matrix view;
	Matrix invView;
};
struct ViewBuffer : public ConstBuffer<ViewData>
{

	ViewBuffer()
		:ConstBuffer(data)
	{
		data.view = XMMatrixIdentity();
		data.invView = XMMatrixIdentity();
	}

	void SetData(Matrix view, Matrix invView)
	{
		data.view = XMMatrixTranspose(view);
		data.invView = XMMatrixTranspose(invView);
	}
	ViewData data;
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

struct RayData
{
	Vector3 origin = {};
	UINT plygonCount;

	Vector3 direction = {};
	float padding;
};
struct RayBuffer : public ConstBuffer<RayData>
{
	RayBuffer()
		:ConstBuffer(data)
	{
	}
	RayData data;


};