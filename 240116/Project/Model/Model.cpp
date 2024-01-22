#include "Framework.h"
#include "Model.h"
Model::Model(string name)
{
	this->name = name;
	ReadMaterial();
	ReadMesh();

	Transform::Load();
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

	if (ImGui::Button("Save Model"))
	{
		Transform::Save();
		for (Material* material : materials)
		{
			material->Save(L"_ModelData/Material/"  + ToWString(name + "/" +material->GetName()) + L".mat");

		}
	}


	if (ImGui::Button("Load Model"))
	{
		Transform::Load();
		for (Material* material : materials)
		{
			material->Load(L"_ModelData/Material/" + ToWString(name + "/" + material->GetName()) + L".mat");

		}
	}
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
	size = data.ReadUint();

	for (UINT i = 0; i < size; i++)
	{
		NodeData node;

		node.index = data.ReadInt();
		node.name = data.ReadString();
		node.parent = data.ReadInt();
		node.transform = data.ReadMatrix();

		nodes.emplace_back(node);
	}

	size = data.ReadUint();

	for (UINT i = 0; i < size; i++)
	{
		BoneData bone;

		bone.index = data.ReadInt();
		bone.name = data.ReadString();
		bone.offset = data.ReadMatrix();

		bones.emplace_back(bone);

		boneMap.emplace(bone.name, bone.index);
	}

}

void Model::CreateMesh()
{
}

