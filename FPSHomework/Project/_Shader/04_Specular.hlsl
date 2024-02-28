#include "Header.hlsli"

struct VertexOutput
{
    float4 pos    : SV_POSITION;
    float2 uv     : UV;
    float3 normal : NORMAL;
    
    float3 cameraDir : CAMERADIR;
};

VertexOutput VS(VertexTextureNormal input)
{
    VertexOutput output;
    
    output.pos = mul( input.pos, world);
    
    ////////////////////////////////
    
    float3 cameraPos = invView._41_42_43;
    
    output.cameraDir = normalize(output.pos.xyz - cameraPos);
    
    ////////////////////////////////
    
    output.pos = mul(output.pos,  view);
    output.pos = mul(output.pos,  proj);
    
    output.normal = mul(normalize(input.normal), (float3x3)world);
    
    output.uv = input.uv;
    
    return output;
}

float4 PS(VertexOutput input) : SV_TARGET
{
    //clamp, saturate
    float3 light = normalize(lightDirection);
    
    float diffuseIntensity = saturate(dot(input.normal, -light)); // N dot L
    
    float4 albedo = diffuseMap.Sample(samp, input.uv);

    float3 reflection = normalize(reflect(light, input.normal));
    
    float specularIntensity = saturate(dot(-reflection, input.cameraDir));
    
    float shininess = 32.0f;
    
    specularIntensity = pow(specularIntensity, shininess);
    
    float4 diffuse = albedo * diffuseIntensity;
    
    float4 specular = specularMap.Sample(samp, input.uv) * specularIntensity;
    
    float4 ambient = albedo * float4(0.1f, 0.1f, 0.1f, 1.0f);
    
    return diffuse + specular + ambient; //Phong - Shading
}