#include "Header.hlsli"
#include "LightHeader.hlsli"

struct VertexInput
{
    float4 pos     : POSITION;
    float2 uv      : UV;
    float3 normal  : NORMAL;
    float3 tangent : TANGENT;
    
    int4 indices   : BLENDINDICES;
    float4 weights : BLENDWEIGHTS;
    
    matrix transform : INSTANCE_TRANSFORM;
    uint   index     : INSTANCE_INDEX;
    
    
};
struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    
    float3 cameraDir : CAMERADIR;
    
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
};

//Texture2DArray transformMap : register(t0);

//struct Frame
//{
//    int clipIndex;
//    uint frameIndex;
//    float time;
//    float speed;
//};

//struct Motion
//{
//    float takeTime;
//    float tweenTime;
//    float runningTime;
//    float padding;

//    Frame curFrame, nextFrame;
//};
#define MAX_INSTANCE 128
cbuffer FrameInstancingBuffer : register(b3)
{
    Motion motions[MAX_INSTANCE];
}

matrix SkinWorld(uint instanceIndex, int4 indices, float4 weights)
{
    matrix transform = 0;

    matrix curAnim, nextAnim;
    
    matrix curFrame, nextFrame;
    
    float4 c[4], n[4];
    
    
    
    for (int i = 0; i < 4; i++)
    {
        int clipIndex[2];
        int frameIndex[2];
        float time[2];
        
        clipIndex[0] = motions[instanceIndex].curFrame.clipIndex;
        frameIndex[0] = motions[instanceIndex].curFrame.frameIndex;
        time[0] = motions[instanceIndex].curFrame.time;
        
        clipIndex[1] = motions[instanceIndex].nextFrame.clipIndex;
        frameIndex[1] = motions[instanceIndex].nextFrame.frameIndex;
        time[1] = motions[instanceIndex].nextFrame.time;
        
        
        c[0] = transformMap.Load(int4(indices[i] * 4 + 0, frameIndex[0], clipIndex[0], 0));
        c[1] = transformMap.Load(int4(indices[i] * 4 + 1, frameIndex[0], clipIndex[0], 0));
        c[2] = transformMap.Load(int4(indices[i] * 4 + 2, frameIndex[0], clipIndex[0], 0));
        c[3] = transformMap.Load(int4(indices[i] * 4 + 3, frameIndex[0], clipIndex[0], 0));
        
        curFrame = matrix(c[0], c[1], c[2], c[3]);
        
        n[0] = transformMap.Load(int4(indices[i] * 4 + 0, frameIndex[0] + 1, clipIndex[0], 0));
        n[1] = transformMap.Load(int4(indices[i] * 4 + 1, frameIndex[0] + 1, clipIndex[0], 0));
        n[2] = transformMap.Load(int4(indices[i] * 4 + 2, frameIndex[0] + 1, clipIndex[0], 0));
        n[3] = transformMap.Load(int4(indices[i] * 4 + 3, frameIndex[0] + 1, clipIndex[0], 0));
        
        nextFrame = matrix(n[0], n[1], n[2], n[3]);
        
        curAnim = lerp(curFrame, nextFrame, time[0]);
        
        if (clipIndex[1] > -1)
        {
            c[0] = transformMap.Load(int4(indices[i] * 4 + 0, frameIndex[1], clipIndex[1], 0));
            c[1] = transformMap.Load(int4(indices[i] * 4 + 1, frameIndex[1], clipIndex[1], 0));
            c[2] = transformMap.Load(int4(indices[i] * 4 + 2, frameIndex[1], clipIndex[1], 0));
            c[3] = transformMap.Load(int4(indices[i] * 4 + 3, frameIndex[1], clipIndex[1], 0));
        
            curFrame = matrix(c[0], c[1], c[2], c[3]);
        
            n[0] = transformMap.Load(int4(indices[i] * 4 + 0, frameIndex[1] + 1, clipIndex[1], 0));
            n[1] = transformMap.Load(int4(indices[i] * 4 + 1, frameIndex[1] + 1, clipIndex[1], 0));
            n[2] = transformMap.Load(int4(indices[i] * 4 + 2, frameIndex[1] + 1, clipIndex[1], 0));
            n[3] = transformMap.Load(int4(indices[i] * 4 + 3, frameIndex[1] + 1, clipIndex[1], 0));
        
            nextFrame = matrix(n[0], n[1], n[2], n[3]);
        
            nextAnim = lerp(curFrame, nextFrame, time[1]);
            
            
            curAnim = lerp(curAnim, nextAnim, motions[instanceIndex].tweenTime);
        }
        
        
        
        transform += mul(weights[i], curAnim);
    }
    
    return transform;
}

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    
    matrix transform = mul(SkinWorld(input.index ,input.indices, input.weights), input.transform);
    
    output.pos = mul(input.pos, transform);
    
    ////////////////////////////////
    
    float3 cameraPos = invView._41_42_43;
    
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