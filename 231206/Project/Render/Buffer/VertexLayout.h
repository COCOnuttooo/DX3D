#pragma once

struct Vertex
{
	Vertex(XMFLOAT3 pos)
		:pos(pos) {}

	XMFLOAT3 pos{};
};

struct VertexColor
{
	VertexColor(XMFLOAT3 pos, XMFLOAT4 color)
		:pos(pos), color(color) {}

	XMFLOAT3 pos;
	XMFLOAT4 color;
};

struct VertexTexture
{
    VertexTexture()
    {
    }

    VertexTexture(Vector3 pos, Vector2 uv)
        :pos(pos), uv(uv)
    {

    }

    Vector3 pos = {};
    Vector2 uv = {};
};

struct VertexTextureNormal
{
    Vector3 pos    = {};
    Vector3 normal = {};
    Vector2 uv     = {};
};
struct VertexColorNormal
{
    VertexColorNormal(XMFLOAT3 pos, XMFLOAT4 color)
        :pos(pos), color(color) 
    {
    }
    Vector3 pos = {};
    Vector3 normal = {};
    Vector4 color = {};
};
