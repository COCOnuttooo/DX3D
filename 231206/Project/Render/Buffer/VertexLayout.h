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
