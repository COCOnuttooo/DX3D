cbuffer RainBuffer : register(b0)
{
    float3 velocity;
    float drawDistance;
   
    float4 color;
   
    float3 origin;
    float time;
   
    float3 size;
    float turbulence;
}
cbuffer Additional : register(b1)
{
    float tailLength;
    float3 randomRot;
    uint drawCount;
}
struct PosDesc
{
    float3 pos;
};

StructuredBuffer<PosDesc> input : register(t0); //SRV


RWStructuredBuffer<PosDesc> output : register(u0);
 void CalulatePos(uint index)
{
    //float3 pos = input[index].pos;
    //float3 normal = pos - origin;
    
    //float3 tangent = cross(normal, velocity);
    //float3 curVelocity;
    
    //float angle = dot(normalize(pos - origin), normalize(velocity));
    //if (angle > turbulence)
    //    curVelocity = velocity;
    //else
    //    curVelocity = cross(tangent, normal);
    
    //curVelocity = normalize(curVelocity);
    
    //pos += 3 * time * curVelocity * length(size) * tailLength;
    ////float3 randRot = cross()
    //if (length(pos - origin) >= 3 * max(max(size.x, size.y), size.z) * tailLength)
    //{
    //    pos = normalize(randomRot) * length(size) + origin;
    //}
    output[index].pos = float3(1, 1, 1);
}

[numthreads(32, 32, 1)]
void CS(uint3 groupID : SV_GroupID, uint groupIndex : SV_GroupIndex)
{
    uint index = groupID * 32 * 32 + groupIndex;
    
    if (drawCount > index)
        CalulatePos(index);
}