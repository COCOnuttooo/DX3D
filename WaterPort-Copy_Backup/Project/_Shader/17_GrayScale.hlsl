#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

VertexOutput VS(VertexTexture input)
{
    VertexOutput output;
    
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    
    output.uv = input.uv;
    
    return output;
}

float4 PS(VertexOutput input) : SV_TARGET
{
    float4 albedo = diffuseMap.Sample(samp, input.uv);
    //float scale = (albedo.r + albedo.g + albedo.b) / 3;
    float3 color;

    //float scale = color.r + color.g + color.b;
    //float scale = dot(albedo.rgb, float3(0.3f, 0.59f, 0.11f));
    float scale = dot(albedo.rgb, albedo.rgb);
    color.r = albedo.r * albedo.r;
    color.g = albedo.g * albedo.g;
    color.b = albedo.b * albedo.b;
    //return float4(color,1.0f);
    return float4(scale,scale,scale, 1.0f);
}