

struct PS_IN
{
	float4 pos   : SV_POSITION;
	float4 depth : POSITION0;
};

float4 ps_main(PS_IN input) : SV_Target
{
	float4 color = input.depth.z / input.depth.w;
	return color;
}