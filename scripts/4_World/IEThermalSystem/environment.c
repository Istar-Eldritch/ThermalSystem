modded class Environment
{

	// Calculates and return temperature of environment
	override protected float GetEnvironmentTemperature()
	{
		float temperature;
		temperature = g_Game.GetMission().GetWorldData().GetBaseEnvTemperature();
		temperature += Math.AbsFloat(temperature * m_Clouds * GameConstants.ENVIRO_CLOUDS_TEMP_EFFECT);

		if (IsWaterContact())
		{
			temperature -= Math.AbsFloat(temperature * GameConstants.ENVIRO_WATER_TEMPERATURE_COEF);
		}

		if (IsInsideBuilding() || m_IsUnderRoofBuilding)
		{
			if (temperature < 20)
				temperature += Math.AbsFloat(temperature * GameConstants.ENVIRO_TEMPERATURE_INSIDE_COEF);
			if (temperature > 40)
				temperature -= Math.AbsFloat(temperature * GameConstants.ENVIRO_TEMPERATURE_INSIDE_COEF);
		}
		else if (IsInsideVehicle())
		{
			if (temperature < 20)
				temperature += Math.AbsFloat(temperature * GameConstants.ENVIRO_TEMPERATURE_INSIDE_VEHICLE_COEF);
			if (temperature > 40)
				temperature -= Math.AbsFloat(temperature * GameConstants.ENVIRO_TEMPERATURE_INSIDE_VEHICLE_COEF);
		}
		else if (IsUnderRoof() && !m_IsUnderRoofBuilding)
		{
			if (temperature < 20)
				temperature += Math.AbsFloat(temperature * GameConstants.ENVIRO_TEMPERATURE_UNDERROOF_COEF);
			if (temperature > 40)
				temperature -= Math.AbsFloat(temperature * GameConstants.ENVIRO_TEMPERATURE_UNDERROOF_COEF);

			temperature -= GameConstants.ENVIRO_TEMPERATURE_WIND_COEF * GetWindModifierPerSurface() * m_Wind;
		}
		else
		{
			temperature -= GameConstants.ENVIRO_TEMPERATURE_WIND_COEF * GetWindModifierPerSurface() * m_Wind;
			temperature -= Math.AbsFloat(temperature * m_Fog * GameConstants.ENVIRO_FOG_TEMP_EFFECT);
			temperature -= GetTemperatureHeightCorrection();
		}

		// incorporate temperature from temperature sources (buffer)
		if (Math.AbsFloat(m_UTSAverageTemperature) > 0.001)
		{
			temperature += m_UTSAverageTemperature;
		}

		return temperature;
	}

	override override void ApplyWetnessToItem(ItemBase pItem)
	{
		super.ApplyWetnessToItem(pItem);
		if (pItem && pItem.IECanHaveTemperature())
		{
			ItemBase parentItem;
			bool isParentWet = false;
			bool parentContainsLiquid = false;
			InventoryLocation iLoc = new InventoryLocation();
			InventoryLocation parentILoc = new InventoryLocation();

			if (pItem.GetInventory().GetCurrentInventoryLocation(iLoc))
			{
				EntityAI parent = iLoc.GetParent();
				if (parent)
				{
					parentItem = ItemBase.Cast(parent);
					if (parentItem)
					{
						parentItem.GetInventory().GetCurrentInventoryLocation(parentILoc);
						if (parentItem.GetWet() >= GameConstants.STATE_SOAKING_WET)
							isParentWet = true;

						if ((parentItem.GetLiquidType() != 0) && (parentItem.GetQuantity() > 0))
							parentContainsLiquid = true;
					}
					else
						isParentWet = true;
				}
			}

			if (isParentWet || parentContainsLiquid)
			{
				float diffTemp = Math.AbsFloat(GameConstants.ENVIRO_TICK_RATE * GameConstants.TEMPERATURE_RATE_COOLING_PLAYER * pItem.GetSoakingIncrement("wetParent")); // used when decreasing temperature
				// Cancel the temperature added by the vanilla impl.
				pItem.AddTemperature(diffTemp);
				if (parentItem.IECanHaveTemperature())
				{ // If the parent container has temperature, temperature aproaches its temperature
					float distanceTemp = Math.AbsFloat(pItem.GetTemperature() - parentItem.GetTemperature());
					if (distanceTemp < diffTemp)
						diffTemp = distanceTemp;

					if (pItem.GetTemperature() > parentItem.GetTemperature())
						diffTemp = diffTemp * -1;
				}
				// TODO: Add an option for this.
				else if (parentILoc.GetSlot() == InventorySlots.BACK) // Items carried on the back shall aproach ambient temperature
				{
					distanceTemp = Math.AbsFloat(pItem.GetTemperature() - GetTemperature());
					if (distanceTemp < diffTemp)
						diffTemp = distanceTemp;

					if (pItem.GetTemperature() > GetTemperature())
						diffTemp = diffTemp * -1;
				}
				else // Items carried somewhere else shall approach body temperature.
				{
					distanceTemp = Math.AbsFloat(pItem.GetTemperature() - PlayerConstants.NORMAL_TEMPERATURE_H);
					if (distanceTemp < diffTemp)
						diffTemp = distanceTemp;

					if (pItem.GetTemperature() > PlayerConstants.NORMAL_TEMPERATURE_H)
						diffTemp = diffTemp * -1;
				}
				if (Math.AbsFloat(diffTemp) > 1)
					pItem.AddTemperature(diffTemp);
			}
		}
	}

	override protected void ApplyDrynessToItemEx(ItemBase pItem, EnvironmentDrynessData pDrynessData)
	{
		super.ApplyDrynessToItemEx(pItem, pDrynessData);
		if (pItem && pItem.IECanHaveTemperature())
		{
			ItemBase parentItem;
			bool isParentWet = false;
			bool parentContainsLiquid = false;

			InventoryLocation iLoc = new InventoryLocation();
			InventoryLocation parentILoc = new InventoryLocation();

			if (pItem.GetInventory().GetCurrentInventoryLocation(iLoc))
			{
				EntityAI parent = iLoc.GetParent();
				if (parent)
				{
					parentItem = ItemBase.Cast(parent);
					if (parentItem)
					{
						parentItem.GetInventory().GetCurrentInventoryLocation(parentILoc);
						if (parentItem.GetWet() >= GameConstants.STATE_SOAKING_WET)
							isParentWet = true;

						if ((parentItem.GetLiquidType() != 0) && (parentItem.GetQuantity() > 0))
							parentContainsLiquid = true;
					}
				}
			}

			float diffTemp;
			float distanceTemp;
			if (!isParentWet && !parentContainsLiquid)
			{
				diffTemp = Math.AbsFloat(GameConstants.ENVIRO_TICK_RATE * GameConstants.TEMPERATURE_RATE_COOLING_PLAYER);
				pItem.AddTemperature(diffTemp);
				if (parentItem.IECanHaveTemperature()) // Parent
				{
					distanceTemp = Math.AbsFloat(pItem.GetTemperature() - parentItem.GetTemperature());
					if (distanceTemp < diffTemp)
						diffTemp = distanceTemp;

					if (pItem.GetTemperature() > parentItem.GetTemperature())
						diffTemp = diffTemp * -1;
				}
				// TODO: Add an option for this.
				else if (parentILoc.GetSlot() == InventorySlots.BACK) // Items carried on the back shall aproach ambient temperature
				{
					distanceTemp = Math.AbsFloat(pItem.GetTemperature() - GetTemperature());
					if (distanceTemp < diffTemp)
						diffTemp = distanceTemp;

					if (pItem.GetTemperature() > GetTemperature())
						diffTemp = diffTemp * -1;
				}
				else
				{
					distanceTemp = Math.AbsFloat(pItem.GetTemperature() - PlayerConstants.NORMAL_TEMPERATURE_H);
					if (distanceTemp < diffTemp)
						diffTemp = distanceTemp;

					if (pItem.GetTemperature() > PlayerConstants.NORMAL_TEMPERATURE_H)
						diffTemp = diffTemp * -1;
				}

				if (Math.AbsFloat(diffTemp) > 1)
					pItem.AddTemperature(diffTemp);
			}

			if (parentContainsLiquid)
			{
				diffTemp = Math.AbsFloat(GameConstants.ENVIRO_TICK_RATE * GameConstants.TEMPERATURE_RATE_COOLING_PLAYER);
				pItem.AddTemperature(diffTemp);
			}

			if (isParentWet)
			{
				diffTemp = Math.AbsFloat(GameConstants.ENVIRO_TICK_RATE * GameConstants.TEMPERATURE_RATE_COOLING_PLAYER * 3.5);
				pItem.AddTemperature(diffTemp);
			}
		}
	}
}