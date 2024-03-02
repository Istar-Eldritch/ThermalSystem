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
		if (CanHaveTemperature())
		{
			auto config = GetThermalSystemConfig();
			float temperature = GetTemperature();
			bool temp_in_range = temperature < config.environment.player_comfort_temp_low || temperature > config.environment.player_comfort_temp_hi;
			if (config.edibles_affect_heat_buffer && temp_in_range)
			{
				float baseDiff;
				if (temperature > config.environment.player_comfort_temp_hi)
					baseDiff = -(config.environment.player_comfort_temp_hi - config.environment.player_comfort_temp_low) - config.environment.player_comfort_temp_low;
				if (temperature < config.environment.player_comfort_temp_low)
					baseDiff = -config.environment.player_comfort_temp_low;
				
				float baseTemp = temperature + baseDiff;
				if (baseTemp > 0)
					baseTemp = Math.Min(baseTemp, 1);
				if (baseTemp < 0)
					baseTemp = Math.Min(baseTemp, -1);
				
				float temp_kg = baseTemp * amount / 1000;
				consumer.GetStatHeatBuffer().Add(temp_kg);
			}
			#ifndef NAMALSK_SURVIVAL
	        float hot_edibles_hurt = config.hot_edibles_hurt;
	        if (hot_edibles_hurt) {
	            float dmg = IECalculateDamageFromTemperature();
	            if (dmg)
	            {
	                consumer.IEAddDamage("Health", dmg, true);
	                consumer.IEAddDamage("Shock", dmg * 3);
	            }
			}
	        #endif
		}
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