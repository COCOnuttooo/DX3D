#pragma once
class Model : public Transform
{
public:
	Model(string name);
	virtual ~Model();
	void Render();
	void Debug();

	void SetShader(wstring file);

	void AttachToBone(class ModelAnimator* model, string boneName);
protected:
	void UpdateSockets();
private:
	void ReadMaterial();
	void ReadMesh();

	void CreateMesh();


protected:
	//string name;


	vector<Material*> materials;
	vector<ModelMesh*> meshes;

	vector<NodeData> nodes;
	vector<BoneData> bones;

	map<string, UINT> boneMap;
	
	map<string, Transform*> sockets;
};
