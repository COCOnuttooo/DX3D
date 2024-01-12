#include "Header.hlsli"
struct VertexTerrain
{
    float4 pos    : POSITION;
    float2 uv     : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
};
struct VertexOutput
{
    float4 pos    : SV_POSITION;
    float2 uv     : UV;
    float3 normal : NORMAL;
    float4 alpha  : ALPHA;

    float3 viewDir : CAMERADIR;

    float3 worldPos : WORLDPOS;

    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
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


    output.normal   = (mul(normalize(input.normal), (float3x3) world));
    output.tangent  = (mul(normalize(input.tangent), (float3x3) world));
    output.binormal = cross(output.normal, output.tangent);
    //output.alpha = input.alpha;
    output.uv = input.uv;
    return output;
}
float4 CalculateBrush(float3 worldPos)
{
    float4 brushColor = float4(0, 0, 0, 0);
    float2 direction  = worldPos.xz - pickedPos.xz;
    switch (type)
    {
    case 0:
        float distance = sqrt(pow(direction.x, 2) + pow(direction.y, 2));

        if (distance < range)
        {
            return brushColor = float4(color, 1.0f);
        }
        break;
    case 1:
        if (abs(direction.x) < range && abs(direction.y) < range)
        {
            return brushColor = float4(color, 1.0f);
        }
        break;
    default:
        return float4(0, 0, 0, 0);
        break;
    }
    return float4(0, 0, 0, 0);

}

Texture2D         alphaMap : register(t10);
Texture2D secondDiffuseMap : register(t11);
float4 PhongShading(VertexOutput input)
{
    float3 light = normalize(lightDirection);
    float4 normalMapping = normalMap.Sample(samp, input.uv);
    //normalMap;

    normalMapping = normalMapping * 2.0f - 1.0f;

    float3x3 TBN = float3x3(input.tangent, input.binormal, input.normal);
    float3 normal = normalize(mul(normalMapping.xyz, TBN));


    //Diffuse Light
    float diffuseIntensity = saturate(dot(normal, -light));
    //albedo = Base Color
    float4 albedo = diffuseMap.Sample(samp, input.uv);
    // Texture Splatting
    float2 tempUV;
    tempUV.x = input.uv.x;
    tempUV.y = 1 - input.uv.y;
    float4 alpha = alphaMap.Sample(samp, tempUV);

    float4 secondAlbedo = secondDiffuseMap.Sample(samp, input.uv);
    albedo = lerp(albedo, secondAlbedo, alpha.b);
    //albedo = lerp(albedo, secondAlbedo, input.alpha.r);
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
float4 PS(VertexOutput input) : SV_TARGET
{
    //clamp, sturate
    float4 brushColor = CalculateBrush(input.worldPos);
    float4 phong = PhongShading(input);
    return phong + brushColor;

}
