#include "Framework.h"
#include "WindEffect.h"

WindEffect::WindEffect(wstring file, Transform* target, float tailLength, UINT drawCount, Vector3 color , float turbulence)
    :target(target), tailLength(tailLength)
{
    this->drawCount = drawCount;
    material->SetShader(L"EffectTest");
    material->SetDiffuseMap(file);

    geometryShader = Shader::AddGS(L"EffectTest");
    buffer = new WeatherBuffer();
    //isAdditive = true;
    buffer->data.color = Vector4(color.x,color.y,color.z,1);
    buffer->data.distance = 1000;
    buffer->data.size = target->scale;
    buffer->data.turbulence = turbulence;
    SetVertex();
    
}

WindEffect::~WindEffect()
{
    delete buffer;

}

void WindEffect::Update()
{
    if (!isActive)
    {
        return;
    }
    buffer->data.time += Time::Delta();
    buffer->data.velocity = -target->GetForwardVector();
    buffer->data.origin = target->GetGlobalPosition();
    buffer->data.size = target->scale;

    for (UINT i = 0; i < drawCount; i++)
    {
        Vector3 velocity;
        Vector3 normal = vertices[i].pos - buffer->data.origin;
        Vector3 tangent = XMVector3Cross(normal, buffer->data.velocity);
        velocity = XMVector3Cross(tangent, normal);
        velocity = velocity.GetNormalized();
        float angle = Vector3(XMVector3Dot(buffer->data.velocity.GetNormalized(), Vector3(vertices[i].pos - buffer->data.origin).GetNormalized())).y;
        if ( angle > buffer->data.turbulence )
            velocity = buffer->data.velocity; 
        
        vertices[i].pos += 3 * DELTA_TIME * velocity * buffer->data.size * tailLength;
        if ((vertices[i].pos - buffer->data.origin).Length() >= 3 * Max(buffer->data.size.x, buffer->data.size.y , buffer->data.size.z) * tailLength)
        {
            Vector3 pos;
            Vector3 rot;
            do
            {
                rot = Vector3(Random(-1.0f, 1.0f), Random(-1.0f, 1.0f), Random(-1.0f, 1.0f)).GetNormalized();
            } while (Vector3(XMVector3Dot(rot, buffer->data.velocity)).x  >0);
            //pos.x = Random(buffer->data.origin.x-buffer->data.size.x, buffer->data.origin.x+buffer->data.size.x);
            //pos.y = Random(buffer->data.origin.y-buffer->data.size.y, buffer->data.origin.y+buffer->data.size.y);
            //pos.z = Random(buffer->data.origin.z-buffer->data.size.z, buffer->data.origin.z+buffer->data.size.z);
            pos = rot * buffer->data.size.Length() + buffer->data.origin;
            vertices[i].pos = pos;
        }
    }
    vertexBuffer->UpdateVertex(vertices.data(), vertices.size());

}

void WindEffect::Render()
{
    if (!isActive)
    {
        return;
    }
    buffer->SetVSBuffer(10);

    Particle::Render();
}

void WindEffect::Debug()
{
    ImGui::Text("Rain Option");
    ImGui::DragFloat3("Velocity", (float*)&buffer->data.velocity, 0.1f);
    ImGui::DragFloat("Distance", (float*)&buffer->data.distance);
    ImGui::DragFloat("Turbulence", (float*)&buffer->data.turbulence, 0.1f, 0.0f, 10.0f);
    ImGui::DragFloat3("Origin", (float*)&buffer->data.origin, 0.1f);
    ImGui::DragFloat3("Size", (float*)&buffer->data.size, 0.1f);
    ImGui::ColorEdit3("Color", (float*)&buffer->data.color);
}

void WindEffect::PlayTargeted()
{
    isActive = true;
    this->position = target->GetGlobalPosition();
}

void WindEffect::SetVertex()
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
    }

    vertexBuffer = new VertexBuffer(vertices);
}
