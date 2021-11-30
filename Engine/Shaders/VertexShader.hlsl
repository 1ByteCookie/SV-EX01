float4 main( float2 Position : POSITION0 ) : SV_POSITION
{
    return float4(Position, 0.0f, 1.0f);
}