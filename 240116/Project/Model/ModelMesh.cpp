#include "Framework.h"
#include "ModelMesh.h"
ModelMesh::ModelMesh(string name, UINT materialIndex, vector<ModelVertex>& vertices, vector<UINT>& indices)
	:Mesh(vertices, indices), name(name), vertices(vertices), indices(indices), materialIndex(materialIndex)
{
}

ModelMesh::~ModelMesh()
{
}

void ModelMesh::Render()
{
	IASet();
	DC->DrawIndexed(indices.size(), 0, 0);

}
