#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 viewDir : CMAERADIR;
};
VertexOutput VS(VertexTextureNormal input)
{
    VertexOutput output;
   // matrix invView = 
    float3 cameraPos =invView._41_42_43;
    
    
    output.pos = mul(input.pos, world);
    output.viewDir = normalize(output.pos.xyz - cameraPos);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    
    output.normal = (mul(normalize(input.normal), (float3x3) world));
    
    output.uv = input.uv;
    return output;
}


float4 PS(VertexOutput input) : SV_TARGET
{
    float3 light = normalize(lightDirection);
    
    float diffuseIntensity = (dot(input.normal, -light));
    
    float4 albedo = diffuseMap.Sample(samp, input.uv);
    /////////////////////////////
    
    float3 reflection = reflect(light, input.normal);
    
    float specularIntensity = dot(-reflection, input.viewDir);
    /////////////////////////////
    
    return albedo * diffuseIntensity * specularIntensity;
}
