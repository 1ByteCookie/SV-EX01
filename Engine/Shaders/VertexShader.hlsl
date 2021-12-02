
struct OutputData
{
    float4 Position : SV_POSITION;
    float4 Color : _COLOR_;
};

struct InputData
{
    float2 Position : POSITION0;
    float4 Color : COLOR0;
};

OutputData main(InputData _Input)
{
    OutputData _Output;
    _Output.Position = float4(_Input.Position, 0.0f, 1.0f);
    _Output.Color = _Input.Color;
    
    return _Output;
}