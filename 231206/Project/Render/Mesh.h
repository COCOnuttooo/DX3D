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