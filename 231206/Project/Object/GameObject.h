#pragma once
template<typename T>
class GameObject
{
public:
	GameObject(wstring shaderFile);
	virtual ~GameObject();
	virtual void Render();
	

protected:
	virtual void CreateMesh() = 0;

protected:
	vector<T>     vertices{};
	vector<UINT>             indices{};

	Mesh* mesh;
	Material* material;

	Matrix worldMatrix;
	MatrixBuffer* worldBuffer;
};

template<typename T>
inline GameObject<T>::GameObject(wstring shaderFile)
{
	material = new Material(shaderFile);
	worldBuffer = new MatrixBuffer;
}

template<typename T>
inline GameObject<T>::~GameObject()
{
	delete worldBuffer;
	delete mesh;
	delete material;
}

template<typename T>
inline void GameObject<T>::Render()
{
	worldBuffer->SetData(worldMatrix);
	worldBuffer->SetVSBuffer(0);
	mesh->IASet();
	material->SetShader();

	if (indices.size() > 0)
		DC->DrawIndexed(indices.size(), 0, 0); //Draw Call
	else
		DC->Draw(vertices.size(), 0);
}
