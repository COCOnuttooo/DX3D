#include "Framework.h"
#include "Transform2.h"
UINT Transform2::index = 0;

Transform2::Transform2()
{
	worldBuffer = new MatrixBuffer();
	world = XMMatrixIdentity();

	name = "Object" + to_string(index++);
}

Transform2::~Transform2()
{
	delete worldBuffer;
}

void Transform2::SetWorld()
{
	worldBuffer->SetData(world);
	worldBuffer->SetVSBuffer(0);
}

void Transform2::Update()
{
	UpdateWorldMatrix();
}

void Transform2::SetParent(Transform* parent)
{
	this->parent = parent;
	if (parent == nullptr)
		translation = globalPosition;

}


void Transform2::Debug()
{
	if (ImGui::TreeNode(name.c_str()))
	{
		char nodeName[128] = "Initial Node Name";
		if (ImGui::InputText("Rename Node", nodeName, IM_ARRAYSIZE(nodeName))) {
			// 여기서 nodeName은 사용자가 입력한 새로운 이름으로 업데이트 됩니다.
		}
		if (ImGui::Button("Set Name"))
		{
			name = nodeName;
		}
		ImGui::Checkbox("IsActive", &isActive);

		ImGui::DragFloat3("Scale", (float*)&scale, 0.01f, 0.01f, 100.0f);
		ImGui::DragFloat3("Rotation", (float*)&rotation, 0.01f, -2 * XM_PI, 2 * XM_PI);
		ImGui::DragFloat3("Translation", (float*)&translation, 10.0f, -2000.0f, 2000.0f);
		if (ImGui::Button("Save"))
			Save();
		if (ImGui::Button("Load"))
			Load();
		ImGui::TreePop();
	}
}

void Transform2::SetName(string name)
{
	this->name = name;
}

void Transform2::Save()
{
	BinaryWriter data("_TextData/Transform2/" + name + ".transform");

	data.WriteData(scale);
	data.WriteData(rotation);
	data.WriteData(translation);
	data.WriteData(pivot);
}

void Transform2::Load()
{
	BinaryReader data("_TextData/Transform2/" + name + ".transform");
	scale = data.ReadVector3();
	rotation = data.ReadVector3();
	translation = data.ReadVector3();
	pivot = data.ReadVector3();
}

void Transform2::UpdateWorldMatrix()
{
	Matrix S = XMMatrixScaling(scale.x, scale.y, scale.z);

	Matrix R = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

	Matrix T = XMMatrixTranslation(translation.x, translation.y, translation.z);

	Matrix P = XMMatrixTranslation(pivot.x, pivot.y, pivot.z);
	Matrix IP = XMMatrixInverse(nullptr, P);

	world = IP * S * R * T * P;

	if (parent != nullptr)
	{
		Matrix temp = parent->TestGetWorld();
		Matrix parentWorld = XMMatrixTranslation
		(
			temp.r[3].m128_f32[0],
			temp.r[3].m128_f32[1],
			temp.r[3].m128_f32[2]
		);
		world *= parentWorld;
	}

	XMFLOAT4X4 fWorld;

	XMStoreFloat4x4(&fWorld, world);

	right = Vector3(fWorld._11, fWorld._12, fWorld._13).GetNormalized();
	up = Vector3(fWorld._21, fWorld._22, fWorld._23).GetNormalized();
	forward = Vector3(fWorld._31, fWorld._32, fWorld._33).GetNormalized();
	globalPosition.x = world.r[3].m128_f32[0];
	globalPosition.y = world.r[3].m128_f32[1];
	globalPosition.z = world.r[3].m128_f32[2];
}