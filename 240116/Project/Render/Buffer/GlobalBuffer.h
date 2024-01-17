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

//ViewBuffer

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
		data.view    = XMMatrixIdentity();
		data.invView = XMMatrixIdentity();
	}

	void SetData(Matrix view, Matrix invView)
	{
		data.view    = XMMatrixTranspose(view);
		data.invView = XMMatrixTranspose(invView);
	}

	ViewData data;
};



struct LightData
{
	Vector3 direction = Vector3(0, -1, 0);
	float   padding;
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
	UINT    polygonCount;

	Vector3 direction = {};
	float   padding;
};

struct RayBuffer : public ConstBuffer<RayData>
{
	RayBuffer()
		:ConstBuffer(data)
	{
	}

	RayData data;
};


struct BrushData
{
	int     type      = 0;
	Vector3 pickedPos = {};

	float   range = 10.0f;
	Vector3 color = { 0, 1, 0 };
};

struct BrushBuffer : public ConstBuffer<BrushData>
{
	BrushBuffer()
		:ConstBuffer(data)
	{
	}

	BrushData data;
};


struct MaterialData
{
	Vector4 diffuse = Vector4(1, 1, 1, 1);
	Vector4 specular = Vector4(0, 0, 0, 1);
	Vector4 ambient = Vector4(0.1f, 0.1f, 0.1f, 1);
	Vector4 emissive = Vector4(0, 0, 0, 0);

	float shininess = 24.0f;

	int hasDiffuseMap = false;
	int hasSpecularMap = false;
	int hasNormalMap = false;
};

struct MaterialBuffer : public ConstBuffer<MaterialData>
{
	MaterialBuffer()
		:ConstBuffer(data)
	{

	}

	void SetData(Matrix view, Matrix invView)
	{

	}

	MaterialData data;
};
