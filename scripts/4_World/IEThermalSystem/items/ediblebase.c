modded class Edible_Base : ItemBase
{

    override bool CanHaveTemperature()
    {
        return GetThermalSystemConfig().edibles_have_temperature;
    }

    bool CanBeConsumedFrozen()
    {
        return GetThermalSystemConfig().can_consume_frozen_edibles;
    }
}