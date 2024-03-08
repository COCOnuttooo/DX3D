#include "Framework.h"
#include "Spark.h"

Spark::Spark(wstring file, bool isAdditive)
{
	this->isAdditive = isAdditive;
	material->SetShader(L"23_Spark");

	material->SetDiffuseMap(file);

	geometryShader = Shader::AddGS(L"23_Spark");

	valueBuffer      = new FloatValueBuffer();
	startColorBuffer = new FloatValueBuffer();
	endColorBuffer	 = new FloatValueBuffer();

	startColorBuffer->data.values[0] = 1.0f;
	  endColorBuffer->data.values[0] = 1.0f;
	startColorBuffer->data.values[1] = 1.0f;
	  endColorBuffer->data.values[1] = 1.0f;
	startColorBuffer->data.values[2] = 1.0f;
	  endColorBuffer->data.values[2] = 1.0f;
	startColorBuffer->data.values[3] = 1.0f;
	  endColorBuffer->data.values[3] = 1.0f;


	SetVertex();
}

Spark::~Spark()
{
	delete valueBuffer;
	delete startColorBuffer;
	delete endColorBuffer;

}

void Spark::Update()
{
	if (!isActive)
		return;


	//value0 : time
	//value1 : duration

	valueBuffer->data.values[0] += DELTA_TIME;

	if (valueBuffer->data.values[0] > valueBuffer->data.values[1])
		Stop();
}

void Spark::Render()
{
	     valueBuffer->SetVSBuffer(10);
	     valueBuffer->SetPSBuffer(10);
	startColorBuffer->SetPSBuffer(11);
	  endColorBuffer->SetPSBuffer(12);
	__super::Render();

}

void Spark::Debug()
{
	ImGui::Text("Spark Option");

	ImGui::SliderInt("Particle Count", (int*)&drawCount, 1, MAX_COUNT);

	ImGui::ColorEdit4("Start Color", startColorBuffer->data.values);
	ImGui::ColorEdit4("  End Color",   endColorBuffer->data.values);



}

void Spark::Play(Vector3 position)
{
	valueBuffer->data.values[0] = 0.0f;

	__super::Play(position);
	UpdateParticle();
	vertexBuffer->UpdateVertex(vertices.data(), drawCount);


}

void Spark::SetVertex()
{
	vertices.resize(MAX_COUNT);

	vertexBuffer = new VertexBuffer(vertices);

	drawCount = 500;

	valueBuffer->data.values[1] = 1.0f;


}

void Spark::UpdateParticle()
{

	for (UINT i = 0; i < drawCount; i++)
	{
		vertices[i].position = position;

		float size = Random(minSize, maxSize);

		vertices[i].size = { size,size };

		Vector3 rot;

		rot.x = Random(0.0f, XM_2PI);
		rot.y = Random(0.0f, XM_2PI);
		rot.z = Random(0.0f, XM_2PI);

		float radius = Random(minRadius, maxRadius);

		Vector3 velocity = Vector3(0, 0, radius);

		Matrix rotMatrix = XMMatrixRotationRollPitchYawFromVector(rot);

		vertices[i].velocity = XMVector3TransformCoord(velocity, rotMatrix);

	}
}
