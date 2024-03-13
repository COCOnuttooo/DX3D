#pragma once

class Model : public Transform
{
protected:
	struct InstanceData
	{
		Matrix world = XMMatrixIdentity();
		UINT   index = 0;
	};

public:
	Model(string name);
	virtual ~Model();

	void Update();
	void Render(bool hasAnimation = false);
	void RenderInstanced(UINT instanceCount);

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
