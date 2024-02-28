#pragma once

class ModelMesh : public Mesh
{
public:
	ModelMesh(string name, UINT materialIndex, vector<ModelVertex>& vertices, vector<UINT>& indices);
	~ModelMesh();

	UINT GetMaterialIndex() { return materialIndex; }

	void Render();

private:
	string name;

	UINT materialIndex;

	vector<ModelVertex> vertices;
	vector<UINT>         indices;
};
