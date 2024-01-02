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
};
VertexOutput VS(VertexTerrain input)
{
    VertexOutput output;
   // matrix invView = 
    float3 cameraPos = invView._41_42_43;
    
    
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
    //clamp, sturate
    
    float3 light = normalize(lightDirection);
    
    float diffuseIntensity = saturate(dot(input.normal, -light));
   
    float4 albedo = diffuseMap.Sample(samp, input.uv);
    /////////////////////////////
    
    float3 reflection = reflect(light, input.normal);
    
    float specularIntensity = saturate(dot(-reflection, input.viewDir));
    /////////////////////////////
    
    float shininess = 16.0f;
    specularIntensity = pow(specularIntensity, shininess);
    
    float4 diffuse = albedo * diffuseIntensity;
    
    float4 specular = specularMap.Sample(samp, input.uv) * specularIntensity;
    
    float4 ambient = albedo * float4(0.1f, 0.1f, 0.1f, 0.1f);
    
    return diffuse + specular + ambient; // phong shading
}
