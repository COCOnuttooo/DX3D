struct VertexTexture
{
    float4 pos : POSITION;
    float2 uv  : UV;
};

struct VertexTextureNormal
{
    float4 pos    : POSITION;
    float2 uv     : UV;
    float3 normal : NORMAL;
};

struct VertexColorNormal
{
    float4 pos    : POSITION;
    float4 color  : COLOR;
    float3 normal : NORMAL;
};

struct VertexTextureNormalTangent
{
    float4 pos     : POSITION;
    float2 uv      : UV;
    float3 normal  : NORMAL;
    float3 tangent : TANGENT;
};

//VS CBuffer
cbuffer World : register(b0)
{
    matrix world;
};

cbuffer View : register(b1)
{
    matrix view;
    matrix invView;
}
    
cbuffer Projection : register(b2)
{
    matrix proj;
}

//PS CBuffer
cbuffer Light : register(b0)
{
    float3 lightDirection;
}


Texture2D  diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D   normalMap : register(t2);

SamplerState     samp : register(s0);