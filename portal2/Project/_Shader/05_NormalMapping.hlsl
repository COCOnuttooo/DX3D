#include "Header.hlsli"

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
    float3 viewDir : CMAERADIR;
};
VertexOutput VS(VertexTextureNormalTangent input)
{
    VertexOutput output;
   // matrix invView = 
    float3 cameraPos = invView._41_42_43;
    
    
    output.pos = mul(input.pos, world);
    output.viewDir = normalize(output.pos.xyz - cameraPos);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    
    output.normal   = (mul(normalize(input.normal) , (float3x3) world));
    output.tangent  = (mul(normalize(input.tangent), (float3x3) world));
    output.biNormal = cross(output.normal, output.tangent);
    output.uv = input.uv;
    return output;
}


float4 PS(VertexOutput input) : SV_TARGET
{
    //clamp, sturate
    
    float3 light = normalize(lightDirection);
    float4 normalMapping = normalMap.Sample(samp, input.uv);
    //normalMap;
    
    normalMapping = normalMapping * 2.0f - 1.0f;
    
    float3x3 TBN = float3x3(input.tangent, input.biNormal, input.normal);
    float3 normal = normalize(mul(normalMapping.xyz, TBN));
    
    
    //Diffuse Light
    float diffuseIntensity = saturate(dot(normal, -light));
    //albedo = Base Color
    float4 albedo = diffuseMap.Sample(samp, input.uv);
    /////////////////////////////specular Light
    
    float3 reflection = reflect(light, normal);
    
    float specularIntensity = saturate(dot(-reflection, input.viewDir));
    /////////////////////////////
    
    float shininess = 16.0f;
    specularIntensity = pow(specularIntensity, shininess);
    
    float4 diffuse = albedo * diffuseIntensity;
    
    float4 specular = specularMap.Sample(samp, input.uv) * specularIntensity;
    /////////////////////Ambient Light
    float4 ambient = albedo * float4(0.1f, 0.1f, 0.1f, 0.1f);
    
    return diffuse + specular + ambient; // phong shading
}
