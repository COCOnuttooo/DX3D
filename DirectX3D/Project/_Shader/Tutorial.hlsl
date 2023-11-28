float4 VS( float4 pos : POSITION ) : SV_POSITION
{
	return pos;
}

float4 PS( float4 pos : SV_Position) : SV_TARGET
{
    return float4(1, 1, 0, 1);
}