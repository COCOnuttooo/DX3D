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
struct WorldData
{
	Matrix matrix;
	int    hasAnimation;
	Vector3 padding;
};

struct WorldBuffer : public ConstBuffer<WorldData>
{
	WorldBuffer()
		:ConstBuffer(data)
	{
		data.matrix = XMMatrixIdentity();
		data.hasAnimation = false;
	}

	void SetData(Matrix value, int hasAnimation = false)
	{
		data.matrix		  = XMMatrixTranspose(value);
		data.hasAnimation = hasAnimation;
	}

	WorldData data;
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
	int     type = 0;

	Vector4 color = {1,1,1,1};
	//Point Light
	Vector3 position  = Vector3(0, 100, 0);
	float range = 100.0f;
	//Spot Light
	float innerRange = 55.0f;
	float outerRange = 70.0f;
	//Capsule Light

	float length = 50.0f;
	int  active = true;
};
#define MAX_LIGHT 10
struct Lights
{
	LightData lights[MAX_LIGHT];


	int     lightCount   = 1;
	Vector3 ambientLight = Vector3(0.1f, 0.1f, 0.1f);
	Vector3 ambientCeil  = Vector3(0.1f, 0.1f, 0.1f);
	float   padding;


};

struct LightBuffer : public ConstBuffer<Lights>
{
	LightBuffer()
		:ConstBuffer(data)
	{
	}

	Lights data;
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
	Vector4 diffuse  = Vector4(1, 1, 1, 1);
	Vector4 specular = Vector4(0, 0, 0, 1);
	Vector4 ambient  = Vector4(0.1f, 0.1f, 0.1f, 1.0f);
	Vector4 emissive = Vector4(0, 0, 0, 0);

	float shininess  = 24.0f;

	int hasDiffuseMap  = false;
	int hasSpecularMap = false;
	int hasNormalMap   = false;
};

struct MaterialBuffer : public ConstBuffer<MaterialData>
{
	MaterialBuffer()
		:ConstBuffer(data)
	{
	}

	MaterialData data;
};

struct FloatValueData
{
	float values[4] = {};
};

struct FloatValueBuffer : public ConstBuffer<FloatValueData>
{
	FloatValueBuffer()
		:ConstBuffer(data)
	{
	}

	FloatValueData data;
};

struct IntValueData
{
	int values[4] = {};
};

struct IntValueBuffer : public ConstBuffer<IntValueData>
{
	IntValueBuffer()
		:ConstBuffer(data)
	{
	}

	IntValueData data;
};


struct WeatherData
{
	Vector3 velocity = { 0,-1,0 };
	float   distance = 100.0f;

	Vector4 color = { 1,1,1,1 };

	Vector3 origin = {};
	float   time = 0.0f;

	Vector3 size = { 50,50,50 };
	float   turbulence = 0.1f;
};

struct WeatherBuffer : public ConstBuffer<WeatherData>
{
	WeatherBuffer()
		:ConstBuffer(data)
	{
	}

	WeatherData data;
};
