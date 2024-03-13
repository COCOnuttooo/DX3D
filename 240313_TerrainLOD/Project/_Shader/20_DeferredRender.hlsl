#include "LightHeader.hlsli"

struct VertexOutput
{
    float4 pos   : SV_POSITION;
    float2 uv    : UV;
};

static const float2 arrBasePos[4] =
{
    float2(-1.0f, +1.0f),
    float2(+1.0f, +1.0f),
    float2(-1.0f, -1.0f),
    float2(+1.0f, -1.0f),
};

VertexOutput VS(uint vertexID : SV_VertexID)
{
    VertexOutput output;
    output.pos = float4(arrBasePos[vertexID].xy, 0.0f, 1.0f);
    
    output.uv  = output.pos.xy;
    
    return output;
}

struct SurfaceData
{
    float  linearDepth;
    float3 color;
    float3 normal;
    float  specInt;
    float  specPow;
};

Texture2D  diffuseTex : register(t10);
Texture2D specularTex : register(t11);
Texture2D   normalTex : register(t12);
Texture2D    depthTex : register(t13);

float ConvertDepthToLinear(float depth)
{
    float linearDepth = proj._43 / (depth - proj._33);

    return linearDepth;
}

SurfaceData UnpackGBuffer(int2 location)
{
    SurfaceData output;
    
    int3 location3 = int3(location, 0);
    
    float depth = depthTex.Load(location3).x;
    
    output.linearDepth = ConvertDepthToLinear(depth);
    
    output.color = diffuseTex.Load(location3).rgb;
    
    float4 specular = specularTex.Load(location3);
    output.specPow  = MIN_SHININESS + specular.x * MAX_SHININESS;
    output.specInt  = specular.y; 
    
    output.normal = normalTex.Load(location3).xyz;
    output.normal = normalize(output.normal * 2.0f - 1.0f);
    
    return output;
}

float3 CalculateWorldPos(float2 pos, float linearDepth)
{
    float4 position;
    
    float2 temp;
    temp.x = 1 / proj._11;
    temp.y = 1 / proj._22;
    
    position.xy = pos.xy * temp * linearDepth;
    position.z = linearDepth;
    position.w = 1.0f;
    
    return mul(position, invView).xyz;
}

float4 PS(VertexOutput input) : SV_TARGET
{
    SurfaceData data = UnpackGBuffer(input.pos.xy);
    
    LightMaterial material;
 
    material.normal   = data.normal;
    material.diffuse  = float4(data.color, 1.0f);
    material.specular = data.specInt;
    material.viewPos  = invView._41_42_43;
    material.worldPos = CalculateWorldPos(input.uv, data.linearDepth);
    
    return CalculateLights(material);
}