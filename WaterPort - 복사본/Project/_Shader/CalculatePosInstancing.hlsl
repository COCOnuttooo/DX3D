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
    uint drawCount;
}
struct RainDesc
{
    float3 velocity;
    float drawDistance;
   
    float4 color;
   
    float3 origin;
    float time;
   
    float3 size;
    float turbulence;
    
    
};

struct AdditionalDesc
{
    float tailLength;
    uint drawCount;
};
struct PosDesc
{
    float3 pos;
};
struct IndexDesc
{
    uint bufferIndex;
};

StructuredBuffer<PosDesc>             input : register(t0); //SRV
StructuredBuffer<RainDesc>            rains : register(t1); //SRV
StructuredBuffer<AdditionalDesc> additional : register(t2); //SRV
StructuredBuffer<IndexDesc>   bufferIndexes : register(t2); //SRV


RWStructuredBuffer<PosDesc> output : register(u0);

float Rand(float2 co)
{
    return frac(sin(dot(co.xy, float2(12.9898, 78.233))) * 43758.5453);
}
float3 GenerateRandomDirection(float3 seed, float3 normal)
{
    float3 randVec;
    randVec.x = Rand(seed.xy) * 2.0f - 1.0f; // -1.0에서 1.0 사이의 값
    randVec.y = Rand(seed.yz) * 2.0f - 1.0f;
    randVec.z = Rand(seed.zx) * 2.0f - 1.0f;
    randVec = normalize(randVec); // 단위 벡터로 만들기

    if (dot(randVec, normal) > 0.0f) // 내적이 양수인 경우 방향 반전
    {
        randVec = -randVec;
    }

    return randVec;
}

void CalulatePos(uint index)
{
    uint tempIndex = bufferIndexes[index].bufferIndex;
    float3 pos = input[index].pos;
   
    float3 normal = pos - origin;
    //float3 normal = pos - float3(0,0,0);
    
    float3 tangent = cross(normal, velocity);
    float3 curVelocity;
    
    float angle = dot(normalize(pos - origin), normalize(velocity));
    if (angle > turbulence)
        curVelocity = velocity;
    else
        curVelocity = cross(tangent, normal);
    
    curVelocity = normalize(curVelocity);
    
    pos += 3 * time * curVelocity * length(size) * tailLength;
    float3 rot;
    float3 seed = input[(index + 1) % drawCount].pos;
    rot = GenerateRandomDirection(seed, velocity);
    if (length(pos - origin) >= 3 * max(max(size.x, size.y), size.z) * tailLength)
    {
        pos = normalize(rot) * length(size) + origin;
    }
    output[index].pos = pos;
}


[numthreads(32, 32, 1)]
void CS(uint3 groupID : SV_GroupID, uint groupIndex : SV_GroupIndex)
{
    uint index = groupID * 32 * 32 + groupIndex;
    
    if (drawCount > index)
        CalulatePos(index);
}