#include "Header.hlsli"
struct VertexTerrain
{
    float4 pos    : POSITION;
    float2 uv     : UV;
    float3 normal : NORMAL;
    float4 alpha  : ALPHA;
};
struct VertexOutput
{
    float4 pos    : SV_POSITION;
    float2 uv     : UV;
    float3 normal : NORMAL;
    float4 alpha  : ALPHA;
    
    float3 viewDir : CAMERADIR;
    
    float3 worldPos : WORLDPOS;
};


cbuffer BrushBuffer : register(b1)
{
    int type;
    float3 pickedPos;
    float range;
    float3 color;
}
VertexOutput VS(VertexTerrain input)
{
    VertexOutput output;
   // matrix invView = 
    float3 cameraPos = invView._41_42_43;
    
    
    output.pos = mul(input.pos, world);
    output.worldPos = output.pos;
    output.viewDir = normalize(output.pos.xyz - cameraPos);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    
    output.normal = (mul(normalize(input.normal), (float3x3) world));
    output.alpha = input.alpha;
    output.uv = input.uv;
    return output;
}


float4 PS(VertexOutput input) : SV_TARGET
{
    //clamp, sturate
    float4 baseColor = diffuseMap.Sample(samp, input.uv);
    float4 brushColor = float4(0, 0, 0, 0);
    float2 direction = input.worldPos.xz - pickedPos.xz;
    float distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
    
    if(distance < range)
    {
        brushColor = float4(color,1.0f);
    }
    return baseColor + brushColor; // phong shading
}
