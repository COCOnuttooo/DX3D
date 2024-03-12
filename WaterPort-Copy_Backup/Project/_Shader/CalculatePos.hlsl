cbuffer RainBuffer : register(b0)
{
    float3 velocity;
    float drawDistance;
   
    float4 color;
   
    float3 origin;
    float time;
   
    float3 size;
    float turbulence;
}



[numthreads(32, 32, 1)]
void CS(uint3 groupID : SV_GroupID, uint groupIndex : SV_GroupIndex)
{
    uint index = groupID * 32 * 32 + groupIndex;
    
    if (polygonCount > index)
        Intersection(index);
}