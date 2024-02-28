modded class Barrel_ColorBase
{
    override bool CanHaveTemperature()
    {
        return IsLiquidPresent() && GetQuantity() > 0;
    }

    override bool IsFrozen()
    {
        return CanHaveTemperature() && GetTemperature() <= 0 && GetLiquidType() == LIQUID_WATER && GetThermalSystemConfig().water_freezes;
    }

}