#pragma once
class Model : public Transform
{
public:
	Model(string name);
	~Model();
	void Render();
	void Debug();
private:
	void ReadMaterial();
	void ReadMesh();

	void CreateMesh();


private:
	//string name;


	vector<Material*> materials;
	vector<ModelMesh*> meshes;


};
