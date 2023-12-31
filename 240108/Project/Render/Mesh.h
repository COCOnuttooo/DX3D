#pragma once
class Mesh
{
public:
	template<typename T>
	Mesh(vector<T>& vertices);

	template<typename T>
	Mesh(vector<T>& vertices, vector<UINT>& indices);

	~Mesh();

	void IASet(D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	void UpdateVertex(void* vertices, UINT count) { vertexBuffer->UpdateVertex(vertices, count); }
	void UpdateIndex(void* data, UINT count) { indexBuffer->UpdateIndex(data, count); }

private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
};

template<typename T>
inline Mesh::Mesh(vector<T>& vertices)
{
	vertexBuffer = new VertexBuffer(vertices);
}

template<typename T>
inline Mesh::Mesh(vector<T>& vertices, vector<UINT>& indices)
{
	vertexBuffer = new VertexBuffer(vertices);
	indexBuffer = new  IndexBuffer(indices);
}