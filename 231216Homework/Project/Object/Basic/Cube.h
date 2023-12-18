#pragma once
class Cube : public GameObject<VertexColor>
{
	typedef VertexColor VertexType;
public:
	Cube(Vector4 color = Vector4(1,0,0,1));
	~Cube();
	void Render();
	void Update();
	virtual void CreateMesh() override;
private:
	Vector4 color;
	
};

