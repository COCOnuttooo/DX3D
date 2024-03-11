#include "Header.hlsli"
#include "LightHeader.hlsli"

LightVertexOutput VS(VertexTextureNormalTangentBlend input)
{
    LightVertexOutput output;
    
    matrix transform;
    
    [branch]
    if (hasAnimation)
        transform = mul(SkinWorld(input.indices, input.weights), world);
    else
        transform = world;
    output.pos = mul(input.pos, transform);
    ////////////////////////////////
    
    float3 cameraPos = invView._41_42_43;
    
    output.worldPos = output.pos;
    
    output.viewPos = cameraPos;
    
    output.cameraDir = normalize(output.pos.xyz - cameraPos);
    
    
    ////////////////////////////////
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    
    output.normal = mul(normalize(input.normal), (float3x3) world);
    output.tangent = mul(normalize(input.tangent), (float3x3) world);
    
    output.binormal = cross(output.normal, output.tangent);
    
    output.uv = input.uv;
    
    
    return output;
}



GBufferOutput PS(LightVertexOutput input)
{
    //float4 albedo = diffuseMap.Sample(samp, input.uv);
    //float3 normal = GetNormal(input.tangent, input.binormal, input.normal, input.uv);
    //float  specularIntensity = specularMap.Sample(samp, input.uv);
    
    LightMaterial material = GetLightMaterial(input);
    
    
    return PackGBuffer(material.diffuse.xyz, material.normal, material.specular.r);
}