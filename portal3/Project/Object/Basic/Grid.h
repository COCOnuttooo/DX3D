#pragma once
class Grid : public GameObject<VertexColor>
{
public:
	Grid();
	~Grid();

	//void Update();

private:

	// GameObject��(��) ���� ��ӵ�
	void CreateMesh() override;

private:
	Vector2 size = { 1000, 1000 };


};
