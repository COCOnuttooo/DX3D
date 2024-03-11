#include "Header.hlsli"
#include "LightHeader.hlsli"


struct VertexOutput
{
    float4 pos       : SV_POSITION;
    float2 uv        : UV;
    float3 normal    : NORMAL;
    
    float3 cameraDir : CAMERADIR;
    
    float3 tangent   : TANGENT;
    float3 binormal  : BINORMAL;
};

VertexOutput VS(VertexTextureNormalTangentBlend input)
{
    VertexOutput output;
    
    matrix transform = mul(SkinWorld(input.indices, input.weights), world);
    
    output.pos = mul(input.pos, transform);
    
    ////////////////////////////////
    
    float3 cameraPos = invView._41_42_43;
    
    output.cameraDir = normalize(output.pos.xyz - cameraPos);
    
    ////////////////////////////////
    
    output.pos = mul(output.pos,  view);
    output.pos = mul(output.pos,  proj);
    
    output.normal  = mul(normalize(input.normal),  (float3x3)world);
    output.tangent = mul(normalize(input.tangent), (float3x3)world);
    
    output.binormal = cross(output.normal, output.tangent);
    
    output.uv = input.uv;
    
    return output;
}

float4 PS(VertexOutput input) : SV_TARGET
{
    //clamp, saturate
    float3 light = normalize(lights[0].direction);
    
    //Normal Mapping
    float4 normalMapping = normalMap.Sample(samp, input.uv);
    
    normalMapping = normalMapping * 2.0f - 1.0f;
    
    float3x3 TBN = float3x3(input.tangent, input.binormal, input.normal);
    
    float3 normal = normalize(mul(normalMapping.xyz, TBN));
    
    //Diffuse Light
    float diffuseIntensity = saturate(dot(normal, -light)); // N dot L
    
    //albedo = Base Color
    float4 albedo = diffuseMap.Sample(samp, input.uv);

    //Specular Light
    float3 reflection = normalize(reflect(light, normal));
    
    float specularIntensity = saturate(dot(-reflection, input.cameraDir));
    
    //float shininess = 32.0f;
    
    specularIntensity = pow(specularIntensity, shininess);
    
    float4 diffuse = albedo * diffuseIntensity * mDiffuse;
    
    float4 specular = specularMap.Sample(samp, input.uv) * specularIntensity * mSpecular;
    
    //Ambient Light
    float4 ambient = albedo * mAmbient;
    
    return diffuse + specular + ambient + mEmissive; //Phong - Shading
}