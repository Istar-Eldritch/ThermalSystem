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
		
		return config.can_consume_frozen_edibles;
    }

	override void ProcessDecay( float delta, bool hasRootAsPlayer )
	{
		auto config = GetThermalSystemConfig();
		if (!CanHaveTemperature() || !IsFrozen() || config.frozen_edibles_decay)
		{
			super.ProcessDecay(delta, hasRootAsPlayer);
		}
	}

    override void OnConsume(float amount, PlayerBase consumer)
    {

        #ifndef NAMALSK_SURVIVAL
        float hot_edibles_hurt = GetThermalSystemConfig().hot_edibles_hurt;
        if (CanHaveTemperature() && hot_edibles_hurt) {
            float dmg = IECalculateDamageFromTemperature();
            if (dmg)
            {
                consumer.IEAddDamage("Health", dmg, true);
                consumer.IEAddDamage("Shock", dmg * 3);
            }
		}
        #endif
    }

	float IECalculateDamageFromTemperature()
	{
		return IECalculateDamageFromTemperature(GetTemperature());
	}
	
	static float IECalculateDamageFromTemperature(float temperature)
	{
        float damage = Math.Pow(1.0257, temperature - 80) - 1;
        if (damage < 0)
            damage = 0;
		return damage;
	}
}