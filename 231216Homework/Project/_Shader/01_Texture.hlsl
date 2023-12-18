struct VertexColor
{
    float4 pos : POSITION;
    float2 uv : UV;
};

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

cbuffer World : register(b0)
{
    matrix world;
}

cbuffer View : register(b1)
{
    matrix view;
}
    
cbuffer Projection : register(b2)
{
    matrix proj;
}

VertexOutput VS(VertexColor input)
{
    VertexOutput output;
    
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    
    output.uv = input.uv;
    
    return output;
}

Texture2D diffuseMap : register(t0);
SamplerState samp : register(s0);

float4 PS(VertexOutput input) : SV_TARGET
{
    return diffuseMap.Sample(samp, input.uv);
}
