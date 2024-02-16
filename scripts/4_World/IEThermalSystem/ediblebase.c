modded class Edible_Base : ItemBase
{

    override bool CanHaveTemperature()
    {
        return GetThermalSystemConfig().edibles_have_temperature;
    }

    bool CanBeConsumedFrozen()
    {
        bool canConsumeIfLiquid = IsLiquidContainer() && IsLiquidPresent() && !(GetLiquidType() == LIQUID_WATER && GetThermalSystemConfig().water_freezes);
        return canConsumeIfLiquid || GetThermalSystemConfig().can_consume_frozen_edibles;
    }
}