modded class Bottle_Base
{
    override bool CanHaveTemperature()
    {
        return GetThermalSystemConfig().edibles_have_temperature && IsLiquidPresent() && GetQuantity() > 0;
    }

    override bool IsFrozen()
    {
        return CanHaveTemperature() && GetTemperature() <= 0 && GetLiquidType() == LIQUID_WATER && GetThermalSystemConfig().water_freezes;
    }

    override bool CanBeConsumedFrozen()
    {
        bool canConsumeIfLiquid = IsLiquidContainer() && IsLiquidPresent() && !IsFrozen();
        return canConsumeIfLiquid || GetThermalSystemConfig().can_consume_frozen_edibles;
    }
}