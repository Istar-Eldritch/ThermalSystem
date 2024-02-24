modded class ItemBase
{
	bool IsTemperatureVisible()
	{
		float player_comfort_temp_low = GetThermalSystemConfig().environment.player_comfort_temp_low;
		float player_comfort_temp_hi = GetThermalSystemConfig().environment.player_comfort_temp_hi;
		return IECanHaveTemperature() && (GetTemperature() < player_comfort_temp_low || GetTemperature() > player_comfort_temp_hi );
	}

	bool IECanHaveTemperature()
	{
		return CanHaveTemperature();
	}

	override void InitItemVariables()
	{
		super.InitItemVariables();
		m_VarTemperatureMin = -273;
		m_VarTemperatureMax = 10000;
		UpdateNetSyncVariableFloat("m_VarTemperature", GetTemperatureMin(),GetTemperatureMax());

		if (CanHaveTemperature())
		{
			Mission mission = GetGame().GetMission();
			if (mission && mission.GetWorldData())
			{
				SetTemperature(mission.GetWorldData().GetBaseEnvTemperature());
			}
		}
	}

	override void ProcessItemTemperature(float delta, bool hasParent, bool hasRootAsPlayer, ItemBase refParentIB)
	{
		float envTemp = GetGame().GetMission().GetWorldData().GetBaseEnvTemperature();
		float tempDiff = 0;
		float tempDistance = 0;
		if (!hasRootAsPlayer && !IsFireplace())
		{
			if (refParentIB && refParentIB.IECanHaveTemperature())
			{
				tempDiff = Math.AbsFloat(delta * GameConstants.TEMPERATURE_RATE_COOLING_INSIDE);
				tempDistance = Math.AbsFloat(GetTemperature() - refParentIB.GetTemperature());
				if (tempDiff * 2 > tempDistance)
				{
					tempDiff = tempDistance / 2;
				}
				// balance temperatures of items containing each other
				// TODO: Take into consideration mass of the item.
				if (GetTemperature() > refParentIB.GetTemperature())
				{
					// Warm the parent and cool the child or warm the child and cool the parent
					tempDiff = tempDiff * -1;
				}
				if (Math.AbsFloat(tempDiff) > 1)
					AddTemperature(tempDiff);
				if (!refParentIB.IsFireplace() && Math.AbsFloat(tempDiff) > 0.1)
					refParentIB.AddTemperature(tempDiff * -1);
			}
			else if (refParentIB)
			{
				tempDiff = Math.AbsFloat(delta * GameConstants.TEMPERATURE_RATE_COOLING_INSIDE);
				tempDistance = Math.AbsFloat(GetTemperature() - envTemp);
				if (tempDiff > tempDistance)
					tempDiff = tempDistance;
				if (GetTemperature() > envTemp)
					tempDiff = tempDiff * -1;
				if (Math.AbsFloat(tempDiff) > 1)
					AddTemperature(tempDiff);
			}
			else
			{
				tempDiff = Math.AbsFloat(delta * GameConstants.TEMPERATURE_RATE_COOLING_GROUND);
				tempDistance = Math.AbsFloat(GetTemperature() - envTemp);
				if (tempDiff > tempDistance)
					tempDiff = tempDistance;

				if (GetTemperature() > envTemp)
					tempDiff = tempDiff * -1;
				// cooling of an item on ground or inside non-itembase (car, ...)
				if (Math.AbsFloat(tempDiff) > 1)
					AddTemperature(tempDiff);
			}
		}
	}
}