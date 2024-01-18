#include "Framework.h"
#include "Model.h"
Model::Model(string name)
{
	this->name = name;
	ReadMaterial();
	ReadMesh();
}

Model::~Model()
{
	for (Material* material : materials)
		delete material;

	materials.clear();

	for (ModelMesh* mesh : meshes)
		delete mesh;

	meshes.clear();
}

void Model::Render()
{

	Transform::SetWorld();

	for (ModelMesh* mesh : meshes)
	{
		materials[mesh->GetMaterialIndex()]->Set();
		mesh->Render();

	}

}

void Model::Debug()
{
	Transform::Debug();
	for (Material* material : materials)
		material->Debug();
}

void Model::ReadMaterial()
{
	string path = "_ModelData/Material/" + name + "/MaterialList.list";

	BinaryReader data(ToWString(path));

	UINT size = data.ReadUint();

	for (UINT i = 0; i < size; i++)
	{
		Material* material = new Material(L"05_NormalMapping");

		string file = data.ReadString();

		material->Load(ToWString(file));

		materials.push_back(material);
	}
}

void Model::ReadMesh()
{
	string path = "_ModelData/Mesh/" + name + ".mesh";

	BinaryReader data(ToWString(path));

	UINT size = data.ReadUint();

	for (UINT i = 0; i < size; i++)
	{

		string name = data.ReadString();

		UINT materialIndex = data.ReadUint();
		vector<ModelVertex> vertices;
		vector<UINT> indices;
		{
			UINT count = data.ReadUint();


			vertices.resize(count);

			void* ptr = vertices.data();

			data.ReadData(&ptr, sizeof(ModelVertex) * count);

		}
		{
			UINT count = data.ReadUint();

			indices.resize(count);

			void* ptr = indices.data();

			data.ReadData(&ptr, sizeof(UINT) * count);
		}

		ModelMesh* mesh = new ModelMesh(name, materialIndex , vertices, indices);


		meshes.push_back(mesh);
	}
}

void Model::CreateMesh()
{
}

