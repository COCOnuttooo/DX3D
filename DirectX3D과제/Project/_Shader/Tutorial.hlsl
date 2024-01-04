cbuffer World : register(b0)
{
    matrix world;
}

struct VertexColor
{
    float4 pos : POSITION;
    float4 color : COLOR;
};

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};
VertexOutput VS( VertexColor input )
{
    VertexColor output;
    output.pos = mul(input.pos, world);
    output.color = input.color;
	return output;
}

float4 PS( VertexOutput input) : SV_TARGET
{
    return input.color;
}