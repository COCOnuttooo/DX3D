#pragma once
typedef VertexColor VertexType;
class Cube : public GameObject<VertexType>
{
public:
	Cube(Vector4 color = Vector4(1,0,0,1));
	~Cube();
	void Render();
	virtual void CreateMesh() override;
private:
	Vector4 color;
};

