
struct InputData
{
    float4 Position : SV_POSITION;
    float4 Color : _COLOR_;
};


float4 main(InputData _Input) : SV_TARGET
{
    return _Input.Color;
}