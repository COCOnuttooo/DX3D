#include "LightHeader.hlsli"

struct VertexOutput //GeometryInput // VS -> GS -> RS -> PS
{
    float4        pos : POSITION0;
    float2       size : SIZE;
    matrix    invView : INVVIEW;
    matrix       view : VIEW;
    matrix projection : PROJECTION;
};

VertexOutput VS(VertexTexture input)
{
    VertexOutput output;
    
    output.pos        = input.pos;
    output.size       = input.uv; 
    output.invView    = invView;
    output.view       = view;
    output.projection = proj;
    
    return output;
}

struct GeometryOutput
{
    float4 pos : SV_POSITION;
    float2 uv  : UV;
};

static const float2 TEXCOORD[4] =
{
    float2(0.0f, 1.0f),
    float2(0.0f, 0.0f),
    float2(1.0f, 1.0f),
    float2(1.0f, 0.0f)
};

[maxvertexcount(4)]
void GS(point VertexOutput input[1],
inout TriangleStream<GeometryOutput> output)
{
    float3 forward = input[0].pos.xyz - input[0].invView._41_42_43;
    forward = normalize(forward);
    
    float3 up = input[0].invView._21_22_23;
    
    float3 right = normalize(cross(up, forward));
    
    float2 halfSize = input[0].size * 0.5f;
    
    float4 vertices[4] =
    {
        float4(input[0].pos.xyz - right * halfSize.x - up * halfSize.y, 1.0f),
        float4(input[0].pos.xyz - right * halfSize.x + up * halfSize.y, 1.0f),
        float4(input[0].pos.xyz + right * halfSize.x - up * halfSize.y, 1.0f),
        float4(input[0].pos.xyz + right * halfSize.x + up * halfSize.y, 1.0f),
    };
    
    for (uint i = 0; i < 4; i++)
    {
        GeometryOutput element;
        
        element.pos = mul(vertices[i], input[0].view);
        element.pos = mul(element.pos, input[0].projection);
        
        element.uv = TEXCOORD[i];
        
        output.Append(element);
    }
};

cbuffer SpriteBuffer : register(b10)
{
    float2 maxFrame;
    float2 curFrame;
}

float4 PS(GeometryOutput input) : SV_TARGET
{
    float2 uv = (input.uv + curFrame) / maxFrame;
    
    return diffuseMap.Sample(samp, uv) * mDiffuse;
}