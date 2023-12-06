#include "Framework.h"
#include "Cube.h"
Cube::Cube()
	:GameObject<VertexType>(L"Tutorial")
{
    CreateMesh();

}

Cube::~Cube()
{
}

void Cube::Render()
{
	static float angle = 0.0f;
	angle += 1.0001f;
	worldMatrix = XMMatrixRotationRollPitchYaw(angle, angle, 0);

	GameObject::Render();
}

void Cube::CreateMesh()
{
    vertices =
    {
        { XMFLOAT3(-0.5f, +0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)}, //0
        { XMFLOAT3(+0.5f, +0.5f, -0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)}, //1
        { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)}, //2
        { XMFLOAT3(+0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)}, //3

        { XMFLOAT3(-0.5f, +0.5f, +0.5f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)}, //4
        { XMFLOAT3(+0.5f, +0.5f, +0.5f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)}, //5
        { XMFLOAT3(-0.5f, -0.5f, +0.5f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)}, //6
        { XMFLOAT3(+0.5f, -0.5f, +0.5f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)}, //7

        //Back-Face Culling
    };
    indices =
    {
        //Front
        0, 1, 2,
        2, 1, 3,

        //Back
        5, 4, 7,
        7, 4, 6,

        //Left
        4, 0, 6,
        6, 0, 2,

        //Right
        1, 5, 3,
        3, 5, 7,

        //Top
        0, 4, 1,
        1, 4, 5,

        //Bottom
        2, 3, 6,
        6, 3, 7
    };
    mesh = new Mesh(vertices, indices);
}
