#pragma once
class Grid : public GameObject<VertexColor>
{
public:
	Grid();
	~Grid();

	//void Update();

private:

	// GameObject을(를) 통해 상속됨
	void CreateMesh() override;

private:
	Vector2 size = { 1000, 1000 };


};

