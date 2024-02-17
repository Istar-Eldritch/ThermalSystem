modded class Bottle_Base
{
    override bool CanHaveTemperature()
    {
        return GetThermalSystemConfig().edibles_have_temperature && IsLiquidPresent();
    }

    override bool CanBeConsumedFrozen()
    {
        bool canConsumeIfLiquid = IsLiquidContainer() && IsLiquidPresent() && !(GetLiquidType() == LIQUID_WATER && GetThermalSystemConfig().water_freezes);
        return canConsumeIfLiquid || GetThermalSystemConfig().can_consume_frozen_edibles;
    }
}