#pragma once
typedef VertexColor VertexType;
class Cube : public GameObject<VertexType>
{
public:
	Cube();
	~Cube();
	void Render();
	virtual void CreateMesh() override;
private:

};

