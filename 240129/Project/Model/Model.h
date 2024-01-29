#pragma once

class Model : public Transform
{
public:
	Model(string name);
	virtual ~Model();

	void Update();
	void Render();
	void Debug();

	void SetShader(wstring file);

	void AttachToBone(class ModelAnimator* model, string boneName);

	void UpdateSockets();

private:
	void ReadMaterial();
	void ReadMesh();

protected:
	vector<Material*> materials;
	vector<ModelMesh*>   meshes;

	vector<NodeData>  nodes;
	vector<BoneData>  bones;

	map<string, UINT> boneMap;

	map<string, Transform*> sockets;
};
