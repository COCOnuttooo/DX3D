#pragma once
class ModelExporter
{
public:
	ModelExporter(string name);
	~ModelExporter();

private:
	string name;

	Assimp::Importer* importer;

	const aiScene* scene;
};

