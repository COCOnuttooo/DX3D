#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    
    float3 cameraDir : CAMERADIR;
    
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    
};
VertexOutput VS(VertexTextureNormalTangent input)
{
    VertexOutput output;
    
    output.pos = mul(input.pos, world);
    
    
    float3 cameraPos = invView._41_42_43;
    
    output.cameraDir = normalize(output.pos.xyz - cameraPos);
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    
    output.normal = mul(normalize(input.normal), (float3x3) world);
    output.tangent = mul(normalize(input.tangent), (float3x3) world);
    
    output.binormal = cross(output.normal, output.tangent);
    
    output.uv = input.uv;
    
    return output;
}

float4 PS(VertexOutput input) : SV_TARGET
{
    //clamp, saturate
        
    float3 light = normalize(lightDirection);
    
    float4 normalMapping = normalMap.Sample(samp, input.uv); // TODO : Sample Normal map
    
    normalMapping = normalMapping * 2.0f - 1.0f;
    
    float3x3 TBN = float3x3(input.tangent, input.binormal, input.normal);
    
    float3 normal = normalize(mul(normalMapping.xyz, TBN));
    
    //Diffuse Light
    float diffuseIntensity = saturate(dot(normal, -light));
    
    float4 albedo = diffuseMap.Sample(samp, input.uv);
    //Spacular Ligt
    float3 reflection = normalize(reflect(light, normal));
    
    float specularIntensity = saturate(dot(-reflection, input.cameraDir));
    
    float shininess = 32.0f;
    
    specularIntensity = pow(specularIntensity, shininess);
    
    float4 diffuse = albedo * diffuseIntensity;
    
    float4 specular = specularMap.Sample(samp, input.uv) * specularIntensity;
    //Ambient Light
    float4 ambient = albedo * float4(0.1f, 0.1f, 0.1f, 1.0f);
    
    return diffuse + specular + ambient; //Phong - Shading
}