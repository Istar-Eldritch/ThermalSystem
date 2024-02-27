modded class Barrel_ColorBase
{
    override bool CanHaveTemperature()
    {
        return IsLiquidPresent() && GetQuantity() > 0;
    }
}