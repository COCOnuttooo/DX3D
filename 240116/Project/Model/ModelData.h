#pragma once

typedef VertexTextureNormalTangentBlend ModelVertex;

struct MeshData
{
	string name;
	UINT materialIndex;

	vector<ModelVertex> vertices;
	vector<UINT>         indices;

};