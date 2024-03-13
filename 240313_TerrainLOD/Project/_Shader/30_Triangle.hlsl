#include "LightHeader.hlsli"

Vertex VS(Vertex input)
{
    return input;
}

struct CHullOutput
{
    float   edgeTessFactor[3] : SV_TessFactor;
    float insideTessFactor    : SV_InsideTessFactor;
};

cbuffer TessFactor : register(b10)
{
    float3 edges;
    float inside;
}

#define NUM_CONTROL_POINTS 3

CHullOutput CHS(InputPatch<Vertex, NUM_CONTROL_POINTS> input)
{
    CHullOutput output;
    
    output.edgeTessFactor[0] = edges[0];
    output.edgeTessFactor[1] = edges[1];
    output.edgeTessFactor[2] = edges[2];
    output.insideTessFactor  = inside;
    
    return output;
}

struct HullOutput
{
    float4 pos : POSITION;
};

[domain("tri")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("CHS")]
HullOutput HS(InputPatch<Vertex, NUM_CONTROL_POINTS> input, uint i : SV_OutputControlPointID)
{
    HullOutput output;
    
    output.pos = input[i].pos;
    
    return output;
}



struct DomainOutput
{
    float4 pos : SV_POSITION;
};

[domain("tri")]
DomainOutput DS(CHullOutput input, float3 domain : SV_DomainLocation,
    const OutputPatch<HullOutput, NUM_CONTROL_POINTS> patch)
{
    DomainOutput output;
    
    output.pos = float4
    (
        patch[0].pos.xyz * domain.x +
        patch[1].pos.xyz * domain.y +
        patch[2].pos.xyz * domain.z,
        1  
    );
    
    return output;
}

float4 PS(DomainOutput input) : SV_TARGET
{
    return float4(1, 1, 0, 1);
}

