#include "Framework.h"
#include "ComputingEffectInstancing.h"
UINT ComputingEffectInstancing::dataCounts = 0;
UINT ComputingEffectInstancing::instanceIndex = 0;
StructuredBuffer* ComputingEffectInstancing::structuredBuffer = nullptr;
vector<vector<PosDesc>> ComputingEffectInstancing::inputs = {};
vector<vector<PosDesc>> ComputingEffectInstancing::outputs = {};
vector<Transform*> ComputingEffectInstancing::targets = {};
vector<UINT> ComputingEffectInstancing::indexes = {};
StructuredBuffer* ComputingEffectInstancing::indexStructuredBuffer = nullptr;
StructuredBuffer* ComputingEffectInstancing::weatherStructuredBuffer = nullptr;
StructuredBuffer* ComputingEffectInstancing::computeStructuredBuffer = nullptr;

ComputingEffectInstancing::ComputingEffectInstancing(wstring file, Transform* target, float tailLength, UINT drawCount, Vector3 color, float turbulence)
    :target(target), tailLength(tailLength)
{
    targets.emplace_back(target);
    if (drawCount <= MAX_COUNT)
        this->drawCount = drawCount;
    else
        this->drawCount = MAX_COUNT;
    material->SetShader(L"EffectTest");
    material->SetDiffuseMap(file);

    geometryShader = Shader::AddGS(L"EffectTest");
    buffer = new WeatherBuffer();
    computeBuffer = new AdditionalCumputeBuffer;
    computeBuffer->data.tailLength = tailLength;
    computeBuffer->data.drawCount = this->drawCount;
    //isAdditive = true;
    buffer->data.color = Vector4(color.x, color.y, color.z, 1);
    buffer->data.distance = 1000;
    buffer->data.size = target->scale;
    buffer->data.turbulence = turbulence;
    posBuffer = new PosBuffer();
    computeShader = Shader::AddCS(L"CalculatePos");
    CreateCompute();
    SetVertex();
    target->Update();

}

ComputingEffectInstancing::~ComputingEffectInstancing()
{
    delete buffer;
    delete posBuffer;
    delete computeBuffer;
}

void ComputingEffectInstancing::Delete()
{
    delete structuredBuffer;
    delete indexStructuredBuffer;
    delete weatherStructuredBuffer;
    delete computeStructuredBuffer;

}

void ComputingEffectInstancing::Update()
{
    if (!isActive)
    {
        return;
    }
    
    buffers[index]->data.time = Time::Delta();
    buffers[index]->data.velocity = -target->GetForwardVector();
    buffers[index]->data.origin = target->GetGlobalPosition();
    buffers[index]->data.size = target->scale;

    //structuredBuffer->UpdateInput(input.data());
    //CalculatePos();
    //vertexBuffer->UpdateVertex(vertices.data(), vertices.size());
}

void ComputingEffectInstancing::Render()
{
    if (!isActive)
    {
        return;
    }
    buffers[index]->SetVSBuffer(10);
    posBuffers[index]->SetVSBuffer(11);
    Particle::Render();
}

void ComputingEffectInstancing::Debug()
{
    ImGui::Text("Rain Option");
    ImGui::DragFloat3("Velocity", (float*)&buffer->data.velocity, 0.1f);
    ImGui::DragFloat("Distance", (float*)&buffer->data.distance);
    ImGui::DragFloat("Turbulence", (float*)&buffer->data.turbulence, 0.1f, 0.0f, 10.0f);
    ImGui::DragFloat3("Origin", (float*)&buffer->data.origin, 0.1f);
    ImGui::DragFloat3("Size", (float*)&buffer->data.size, 0.1f);
    ImGui::ColorEdit3("Color", (float*)&buffer->data.color);
}

void ComputingEffectInstancing::PlayTargeted()
{
    isActive = true;
    this->position = target->GetGlobalPosition();
}

void ComputingEffectInstancing::CalculatePos()
{
    Vector3 rot;
    do
    {
        rot = Vector3(Random(-1.0f, 1.0f), Random(-1.0f, 1.0f), Random(-1.0f, 1.0f));
    } while (Vector3(XMVector3Dot(rot, buffer->data.velocity)).x > 0);
    rot = rot.GetNormalized();
    computeBuffer->data.randomRot = rot;


    buffer->SetCSBuffer(0);
    computeBuffer->SetCSBuffer(1);
    DC->CSSetShaderResources(0, 1, &structuredBuffer->GetSRV());
    DC->CSSetUnorderedAccessViews(0, 1, &structuredBuffer->GetUAV(), nullptr);

    computeShader->SetShader();

    UINT x = ceilf(drawCount / 1024.0f);

    DC->Dispatch(x, 1, 1);



    structuredBuffer->Copy(output.data(), sizeof(PosDesc) * drawCount);

    for (UINT i = 0; i < input.size(); i++)
    {
        input[i].pos = output[i].pos;
        posBuffer->data.pos[i] = Vector4(output[i].pos.x, output[i].pos.y, output[i].pos.z, 0);
    }

}

void ComputingEffectInstancing::CalculatePosInstanced()
{
    structuredBuffer->UpdateInput(inputs.data());

}

void ComputingEffectInstancing::CreateCompute()
{
    input.resize(drawCount);
    output.resize(drawCount);
    inputs.emplace_back(input);
    outputs.emplace_back(output);
    dataCounts += input.size();
    index = instanceIndex++;
    if (structuredBuffer)
    {
        delete structuredBuffer;
    }
    structuredBuffer = new StructuredBuffer
    {
        inputs.data(),
        sizeof(PosDesc),
        dataCounts,
        sizeof(PosDesc),
        dataCounts
    };
}

void ComputingEffectInstancing::SetVertex()
{

    vertices.resize(drawCount);

    for (UINT i = 0; i < drawCount; i++)
    {
        Vector2 size;

        size.x = Random(0.1f * target->scale.x, 0.4f * target->scale.x);
        size.y = Random(2.0f * target->scale.y, 2.0f * target->scale.y);

        vertices[i].uv = size;

        Vector3 pos;
        //Vector3 rot;
        //rot.x = Random(0.0f, 1.0f);
        //rot.y = Random(0.0f, 1.0f);
        //rot.z = Random(0.0f, 1.0f);

        //pos = rot * target->GetGlobalScale().x;


        pos.x = Random(-buffer->data.size.x, +buffer->data.size.x);
        pos.y = Random(-buffer->data.size.y, +buffer->data.size.y);
        pos.z = Random(-buffer->data.size.z, +buffer->data.size.z);

        vertices[i].pos = pos;
        vertices[i].index = i;
        posBuffer->data.pos[i] = Vector4(pos.x, pos.y, pos.z, 0);
        input[i].pos = pos;
    }

    vertexBuffer = new VertexBuffer(vertices);

}
