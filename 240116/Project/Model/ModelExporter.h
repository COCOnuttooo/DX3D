#pragma once
class ModelExporter
{
public:
	ModelExporter(string name);
	~ModelExporter();

	void ExportMaterial();
	void ExportMesh();
private:
	void ReadMaterial();
	void WriteMaterial();
	void ReadMesh(aiNode* node);
	void WriteMesh();

	wstring CreateTexture(string file);
private:
	string name;

	Assimp::Importer* importer;

	const aiScene* scene;

	vector<Material*> materials;

	vector<MeshData*> meshes;
};

