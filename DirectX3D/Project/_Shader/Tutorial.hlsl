cbuffer World : register(b0)
{
    matrix rotation;
    matrix view;
    matrix proj;
};

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
    VertexOutput output;
    output.pos = mul(input.pos, rotation);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, proj);
    output.color = input.color;
	return output;
}

float4 PS( VertexOutput input) : SV_TARGET
{
    return input.color;
}