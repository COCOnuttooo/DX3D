#include "Framework.h"
#include "TerrainEditor.h"

TerrainEditor::TerrainEditor()
	:GameObject(L"06_TerrainEditor")
{
	CreateMesh();


	polygonCount = indices.size() / 3;

	input.resize(polygonCount);
	output.resize(polygonCount);
	for (UINT i = 0; i < polygonCount; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		input[i].v0 = vertices[index0].pos;
		input[i].v1 = vertices[index1].pos;
		input[i].v2 = vertices[index2].pos;

	}

	computeShader = Shader::AddCS(L"07_ComputePicking");

	rayBuffer = new RayBuffer();
	structuredBuffer = new StructuredBuffer(input.data(), sizeof(InputDesc),input.size(),sizeof(OutputDesc), output.size());

	brushBuffer = new BrushBuffer;
	brushBuffer->data.type = 1;

}

TerrainEditor::~TerrainEditor()
{
	delete brushBuffer;
	delete rayBuffer;
	delete structuredBuffer;
}

void TerrainEditor::Picking()
{
	Ray ray = CAMERA->ScreenPointToRay(mousePos);
	rayBuffer->data.origin = ray.origin;
	rayBuffer->data.direction = ray.direction;
	rayBuffer->data.plygonCount = polygonCount;
	rayBuffer->SetCSBuffer(0);
	//DC->CSSetConstantBuffers(0, 1, &rayBuffer);
	for (UINT z = 0; z < height - 1; z++)
	{
		for (UINT x = 0; x < width -1; x++)
		{
			UINT index[4];
			index[0] = (x + 0) + (z + 0) * width;
			index[1] = (x + 1) + (z + 0) * width;
			index[2] = (x + 0) + (z + 1) * width;
			index[3] = (x + 1) + (z + 1) * width;

			Vector3 pos[4];
			for (UINT i = 0; i < 4; i++)
			{
				pos[i] = vertices[index[i]].pos;
			}
			float distance = 0.0f;
			if (TriangleTests::Intersects(ray.origin, ray.direction, pos[0], pos[1],pos[2], distance))
			{
				pickedPos = ray.origin + ray.direction * distance;
				return;
			}
			if (TriangleTests::Intersects(ray.origin, ray.direction, pos[2], pos[1], pos[3], distance))
			{
				pickedPos = ray.origin + ray.direction * distance;
				return;
			}
		}
	}

}

void TerrainEditor::ComputePicking()
{
	Vector3 calcMouseMove = oldPos - mousePos;

	if (calcMouseMove.Length() == 0)
		return;
	Ray ray = CAMERA->ScreenPointToRay(mousePos);
	rayBuffer->data.origin      = ray.origin;
	rayBuffer->data.direction   = ray.direction;
	rayBuffer->data.plygonCount = polygonCount;
	rayBuffer->SetCSBuffer(0);
	DC->CSSetShaderResources(0, 1, &structuredBuffer->GetSRV());
	DC->CSSetUnorderedAccessViews(0, 1, &structuredBuffer->GetUAV(), nullptr);
	computeShader->SetShader();
	UINT x = ceilf(polygonCount/64.0f);
	DC->Dispatch(x, 1, 1);

	structuredBuffer->Copy(output.data(), sizeof(OutputDesc) * polygonCount);
	float minDistance = FLT_MAX;
	int minIndex = -1;
	UINT index = 0;


	for (auto& data : output)
	{
		if (data.isPicked)
		{
			//break;
			if (minDistance > data.distance)
			{
				minDistance = data.distance;
				minIndex = index;
			}
		}
		index++;
	}

	if (minIndex >= 0)
	{
		pickedPos = ray.origin + ray.direction * minDistance;
	}
	
	brushBuffer->data.pickedPos = pickedPos;

	oldPos = mousePos;
}

void TerrainEditor::Debug()
{
	if (ImGui::TreeNode("Terrain Editor Option"))
	{
		ImGui::Text("Picked Pos : %.1f, %.1f, %.1f", pickedPos.x, pickedPos.y, pickedPos.z);


		ImGui::DragFloat("Brush Radius", &brushBuffer->data.range, 1.0f, 1.0f, 30.0f);

		ImGui::DragFloat("Adjust Value", &adjustValue, 1.0f, -30.f, 30.0f);
		if (ImGui::RadioButton("Circle",    brushBuffer->data.type == 0)) 
		{ 
			brushBuffer->data.type = 0;
		}
		ImGui::SameLine();
		if (ImGui::RadioButton("Rectangle", brushBuffer->data.type == 1)) 
		{ 
			brushBuffer->data.type = 1;
		}

		ImGui::TreePop();
	}
}

void TerrainEditor::Render(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	brushBuffer->SetPSBuffer(1);

	GameObject::Render(topology);
}

void TerrainEditor::Update()
{
	if (KEY_DOWN('K'))
	{
		brushBuffer->data.type = ++brushBuffer->data.type % 2;
	}
	GameObject::Update();
	ComputePicking();
	if (KEY_PRESS(VK_LBUTTON))
	{
		AdjustHeight();
	}
}

void TerrainEditor::CreateMesh()
{
	vector<Vector4> colors;
	if (heightMap)
	{
		colors = heightMap->ReadPixels();
		width = heightMap->GetSize().x;
		height = heightMap->GetSize().y;
	}
	for (UINT z = 0; z < height; z++)
	{
		for (UINT x = 0; x < width; x++)
		{
			VertexType vertex;

			vertex.pos = Vector3(x, 0, z);
			vertex.uv.x = (float)x / (width - 1);
			vertex.uv.y = 1.0f - (float)z / (height - 1);

			UINT index = x + width * z;
			if (!colors.empty())
				vertex.pos.y = colors[index].x * HEIGHT_SCALE;
			vertices.emplace_back(vertex);
		}
	}
	for (UINT i = 0; i < height - 1; i++)
	{
		for (UINT j = 0; j < width - 1; j++)
		{
			indices.emplace_back((i + 0) * (width)+(j + 0));
			indices.emplace_back((i + 1) * (width)+(j + 0));
			indices.emplace_back((i + 0) * (width)+(j + 1));


			indices.emplace_back((i + 1) * (width)+(j + 0));
			indices.emplace_back((i + 1) * (width)+(j + 1));
			indices.emplace_back((i + 0) * (width)+(j + 1));
		}
	}

	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		Vector3 v01 = vertices[index1].pos - vertices[index0].pos;
		Vector3 v02 = vertices[index2].pos - vertices[index0].pos;

		Vector3 normal = Vector3::Cross(v01, v02);

		vertices[index0].normal += normal;
		vertices[index1].normal += normal;
		vertices[index2].normal += normal;
	}
	mesh = new Mesh(vertices, indices);
}

void TerrainEditor::AdjustHeight()
{

	switch (brushBuffer->data.type)
	{
	case 0:
		for (VertexType& vertex : vertices)
		{
			Vector3 p1 = Vector3(vertex.pos.x, 0.0f, vertex.pos.z);
			Vector3 p2 = Vector3(brushBuffer->data.pickedPos.x, 0.0f, brushBuffer->data.pickedPos.z);

			float distance = Vector3(p1 - p2).Length();

			float value = adjustValue;

			if (distance <= brushBuffer->data.range)
			{
				vertex.pos.y += value * Time::Delta();
				//vertex.pos.y;
				//continue;
			}

			vertex.pos.y = Clamp(vertex.pos.y, 0.0f, MAX_HEIGHT);
			vertex.normal = Vector3();
		}
		break;
	case 1:
		for (VertexType& vertex : vertices)
		{
			float x = vertex.pos.x;
			float z = vertex.pos.z;
			float L = brushBuffer->data.pickedPos.x - brushBuffer->data.range;
			float R = brushBuffer->data.pickedPos.x + brushBuffer->data.range;
			float T = brushBuffer->data.pickedPos.z + brushBuffer->data.range;
			float B = brushBuffer->data.pickedPos.z - brushBuffer->data.range;
			float value = adjustValue;
			if (x >= L && x <= R && z >= B && z <= T)
			{
				vertex.pos.y += value * Time::Delta();
				//vertex.pos.y;
				//continue;
			}

			vertex.pos.y = Clamp(vertex.pos.y, 0.0f, MAX_HEIGHT);
			vertex.normal = Vector3();
		}
		break;

	default:
		break;
	}
	
	for (UINT i = 0; i < indices.size() / 3; i++)
	{
		UINT index0 = indices[i * 3 + 0];
		UINT index1 = indices[i * 3 + 1];
		UINT index2 = indices[i * 3 + 2];

		Vector3 v01 = vertices[index1].pos - vertices[index0].pos;
		Vector3 v02 = vertices[index2].pos - vertices[index0].pos;

		Vector3 normal = Vector3::Cross(v01, v02).GetNormalized();

		vertices[index0].normal += normal;
		vertices[index1].normal += normal;
		vertices[index2].normal += normal;
		//update input
		input[i].v0 = vertices[index0].pos;
		input[i].v1 = vertices[index1].pos;
		input[i].v2 = vertices[index2].pos;
	}
	
	
	mesh->UpdateVertex(vertices.data(), vertices.size());
	structuredBuffer->UpdateInput(input.data());
}

