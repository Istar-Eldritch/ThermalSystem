modded class Edible_Base : ItemBase
{

    override bool CanHaveTemperature()
    {
        return GetThermalSystemConfig().edibles_have_temperature;
    }

    bool CanBeConsumedFrozen()
    {
		auto config = GetThermalSystemConfig();
        if (!config.can_consume_frozen_edibles)
		{
			foreach(string cls: config.frozen_edibles)
			{
				if (GetGame().IsKindOf(GetType(), cls))
				{
					return true;
				}
			}
		}
		
		return config.can_consume_frozen_edibles
    }
}