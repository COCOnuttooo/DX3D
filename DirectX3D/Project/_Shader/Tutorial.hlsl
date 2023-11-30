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
	return input;
}

float4 PS( VertexOutput input) : SV_TARGET
{
    return input.color;
}