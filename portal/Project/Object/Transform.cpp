#include "Framework.h"
#include "Transform.h"
UINT Transform::index = 0;

Transform::Transform()
{
	worldBuffer = new MatrixBuffer();
	world = XMMatrixIdentity();

	name = "Object" + to_string(index++);
}

Transform::~Transform()
{
	delete worldBuffer;
}

void Transform::SetWorld()
{
	worldBuffer->SetData(world);
	worldBuffer->SetVSBuffer(0);
}

void Transform::Update()
{
	UpdateWorldMatrix();
}

void Transform::Debug()
{
	if (ImGui::TreeNode(name.c_str()))
	{
		char nodeName[128] = "Initial Node Name";
		if (ImGui::InputText("Rename Node", nodeName, IM_ARRAYSIZE(nodeName))) {
			// ���⼭ nodeName�� ����ڰ� �Է��� ���ο� �̸����� ������Ʈ �˴ϴ�.
		}
		if (ImGui::Button("Set Name"))
		{
			name = nodeName;
		}
		ImGui::Checkbox("IsActive", &isActive);

		ImGui::DragFloat3("Scale",       (float*)&scale,       0.01f, 0.01f, 100.0f);
		ImGui::DragFloat3("Rotation",    (float*)&rotation,    0.01f,-2* XM_PI, 2* XM_PI);
		ImGui::DragFloat3("Translation", (float*)&translation, 0.1f, -2000.0f, 2000.0f);
		if (ImGui::Button("Save"))
			Save();
		if (ImGui::Button("Load"))
			Load();
		ImGui::TreePop();
	}
}

void Transform::SetName(string name)
{
	this->name = name;
}

void Transform::SetRotation(const XMMATRIX& matrix)
{
	// ȸ�� ��Ŀ��� Pitch, Yaw, Roll ���� ���
	float pitch, yaw, roll;

	// Pitch (X�� ȸ��)
	pitch = asinf(matrix._32); // M32�� 3�� 2�� ���

	// Gimbal lock�� üũ
	if (cosf(pitch) > 0.0001) // Gimbal lock�� �ƴ� ���
	{
		roll = atan2f(-matrix._31, matrix._33); // M31�� M33 ���
		yaw = atan2f(-matrix._12, matrix._22); // M12�� M22 ���
	}
	else // Gimbal lock�� ���
	{
		roll = 0.0f;
		yaw = atan2f(matrix._21, matrix._11); // M21�� M11 ���
	}

	// ���ȿ��� ��(degree) ������ ��ȯ
	pitch = XMConvertToDegrees(pitch);
	yaw = XMConvertToDegrees(yaw);
	roll = XMConvertToDegrees(roll);

	// Vector3 ȸ���� �Ҵ�
	rotation = Vector3(pitch, yaw, roll);
}

void Transform::Save()
{
	BinaryWriter data("_TextData/Transform/" + name + ".transform");

	data.WriteData(scale);
	data.WriteData(rotation);
	data.WriteData(translation);
	data.WriteData(pivot);
}

void Transform::Load()
{
	BinaryReader data("_TextData/Transform/" + name + ".transform");
	scale = data.ReadVector3();
	rotation= data.ReadVector3();
	translation= data.ReadVector3();
	pivot = data.ReadVector3();
}

void Transform::UpdateWorldMatrix()
{
	Matrix S = XMMatrixScaling(scale.x, scale.y, scale.z);

	Matrix R = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);

	Matrix T = XMMatrixTranslation(translation.x, translation.y, translation.z);

	Matrix P = XMMatrixTranslation(pivot.x, pivot.y, pivot.z);
	Matrix IP = XMMatrixInverse(nullptr, P);

	world = IP * S * R * T * P;

	if (parent != nullptr)
		world *= parent->world;

	XMFLOAT4X4 fWorld;

	XMStoreFloat4x4(&fWorld, world);

	right = Vector3(fWorld._11, fWorld._12, fWorld._13).GetNormalized();
	up = Vector3(fWorld._21, fWorld._22, fWorld._23).GetNormalized();
	forward = Vector3(fWorld._31, fWorld._32, fWorld._33).GetNormalized();

	XMVECTOR outS, outR, outT;

	XMMatrixDecompose(&outS, &outR, &outT, world);
	globalScale    = outS;
	globalRotation = outR;
	globalPosition = outT;

}
