#include "Header.hlsli"


struct LightData
{
    float3 direction;
    int    type;
    
    float4 color;
    float3 position;
    float  range;
    float  inner;
    float  outer;
    int    active;
};

struct LightMaterial
{
    float3 normal;
    float4 diffuse;
    float4 specular;
    
    
    float3 viewPos;
    float3 worldPos;
    
};

struct LightVertexOutput
{
    float4 pos       : SV_POSITION;
    float2 uv        : UV;
    float3 normal    : NORMAL;
    
    float3 cameraDir : CAMERADIR;
    
    float3 tangent   : TANGENT;
    float3 binormal  : BINORMAL;
    
    float3 viewPos  : POSITION0;
    float3 worldPos : POSITION1;
    
};
//PS CBuffer
#define MAX_LIGHT 10
cbuffer LightBuffer : register(b0)
{
    LightData lights[MAX_LIGHT];
    
    int lightCount;
    
    float3 ambientLight;
    float3 ambientCeil;
}

float3 GetNormal(float3 T, float3 B, float3 N, float2 uv)
{
    float4 normalMapping = normalMap.Sample(samp, uv);
    
    normalMapping = normalMapping * 2.0f - 1.0f;
    
    float3x3 TBN = float3x3(T, B, N);
    
    float3 normal = normalize(mul(normalMapping.xyz, TBN));
    
    return normal;
}

LightMaterial GetLightMaterial(LightVertexOutput input)
{
    LightMaterial material;
    
    material.normal = GetNormal(input.tangent, input.binormal, input.normal, input.uv);
    material.diffuse = diffuseMap.Sample(samp, input.uv);
    
    material.specular = specularMap.Sample(samp, input.uv);
    material.viewPos = input.viewPos;
    material.worldPos = input.worldPos;
    
    
    return material;
    
}

float4 CalculateAmbient(LightMaterial material)
{
    float up = material.normal.y * 0.5f + 0.5f;
    
    
    
    float4 result = float4(ambientLight + up * ambientCeil, 1.0f);
    
    
    return result * material.diffuse * mAmbient;
}

float4 CalculateDirectional(LightMaterial material, LightData data)
{
    
    float3 light = normalize(data.direction);
    
    float diffuseIntensity = saturate(dot(material.normal, -light));
    
    float4 diffuse = material.diffuse * diffuseIntensity * mDiffuse;
    
    float3 viewDir = normalize(material.worldPos - material.viewPos);
    
    float3 halfVector = normalize(viewDir + light);
    
    float specularIntensity = saturate(dot(-halfVector, material.normal));
    
    specularIntensity = pow(specularIntensity, shininess);
    
    float4 specular = material.specular * specularIntensity * mSpecular;
    
    
    
    float4 finalColor = diffuse + specular;
    
    return finalColor * data.color;
    
    
}
float4 CalculatePoint(LightMaterial material, LightData data)
{
    float3 light = material.worldPos - data.position;
    
    float lightDistance = length(light);
    
    light = normalize(light);
    
    float diffuseIntensity = saturate(dot(material.normal, -light));
    
    float4 diffuse = material.diffuse * diffuseIntensity * mDiffuse;
    
    float3 viewDir = normalize(material.worldPos - material.viewPos);
    
    float3 halfVector = normalize(viewDir + light);
    
    float specularIntensity = saturate(dot(-halfVector, material.normal));
    
    specularIntensity = pow(specularIntensity, shininess);
    
    float4 specular = material.specular * specularIntensity * mSpecular;
    
    //////////////////////
    
    float lightDistanceNormal = 1.0f - saturate(lightDistance / data.range);
    float attention = pow(lightDistanceNormal, 2);
    
    
    float4 finalColor = diffuse + specular;
    
    return finalColor * data.color * attention;
}
float4 CalculateSpot(LightMaterial material, LightData data)
{
    float4 finalColor;
    
    return finalColor;
}
float4 CalculateCapsule(LightMaterial material, LightData data)
{
    float4 finalColor;
    
    return finalColor;
}

float4 CalculateLights(LightMaterial material)
{
    float4 color = 0;
    
    return color;
}