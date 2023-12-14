#pragma once

template <typename T>
class GameObject : public Transform
{
public:
	GameObject(wstring shaderFile);
	virtual ~GameObject();

	virtual void Render();

	Material* GetMaterial() { return material; }

protected:
	virtual void CreateMesh() = 0;

protected:
	vector<T>    vertices;
	vector<UINT>  indices;

	Mesh* mesh;
	Material* material;
};

template<typename T>
inline GameObject<T>::GameObject(wstring shaderFile)
{
	material = new Material(shaderFile);
}

template<typename T>
inline GameObject<T>::~GameObject()
{
	delete mesh;
	delete material;
}

template<typename T>
inline void GameObject<T>::Render()
{
	Transform::SetWorld();

	mesh->IASet();
	material->Set();

	if (indices.size() > 0)
		DC->DrawIndexed(indices.size(), 0, 0);
	else
		DC->Draw(vertices.size(), 0);
}

