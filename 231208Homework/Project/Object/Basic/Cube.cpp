#include "Framework.h"
#include "Cube.h"
Cube::Cube(Vector4 color)
	:GameObject<VertexType>(L"Tutorial"), color(color)
{
    CreateMesh();

}

Cube::~Cube()
{
}

void Cube::Render()
{
	//static float angle = 0.0f;
	//angle += 1.0001f;
	//world = XMMatrixRotationRollPitchYaw(angle, angle, 0);

	GameObject::Render();
}

void Cube::CreateMesh()
{
    vertices =
    {
        { XMFLOAT3(-0.5f, +0.5f, -0.5f), color}, //0
        { XMFLOAT3(+0.5f, +0.5f, -0.5f), color}, //1
        { XMFLOAT3(-0.5f, -0.5f, -0.5f), color}, //2
        { XMFLOAT3(+0.5f, -0.5f, -0.5f), color}, //3

        { XMFLOAT3(-0.5f, +0.5f, +0.5f), color}, //4
        { XMFLOAT3(+0.5f, +0.5f, +0.5f), color}, //5
        { XMFLOAT3(-0.5f, -0.5f, +0.5f), color}, //6
        { XMFLOAT3(+0.5f, -0.5f, +0.5f), color}, //7

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
