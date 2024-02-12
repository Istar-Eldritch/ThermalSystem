modded class ItemBase
{
    bool IsTemperatureVisible() {
        return CanHaveTemperature() && GetTemperature() > 30;
    }
	
	override void InitItemVariables()
	{
		super.InitItemVariables();
		
		if (CanHaveTemperature())
		{
			Mission mission = GetGame().GetMission();
			if (mission && mission.GetWorldData())
			{
				SetTemperature( mission.GetWorldData().GetBaseEnvTemperature() );
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
			if (hasRootAsPlayer)
			{
				tempDiff = Math.AbsFloat(delta * GameConstants.TEMPERATURE_RATE_COOLING_INSIDE);
				float playerTemp = PlayerConstants.NORMAL_TEMPERATURE_H;
				tempDistance = Math.AbsFloat(GetTemperature() - PlayerConstants.NORMAL_TEMPERATURE_H);
				if (tempDiff > tempDistance) {
					tempDiff = tempDistance;
				}
				if (GetTemperature() > PlayerConstants.NORMAL_TEMPERATURE_H) {
					tempDiff = tempDiff * -1;
				}
				
				if (Math.AbsFloat(tempDiff) > 1)
					AddTemperature(tempDiff);
	
				// #TODO Warm or cool player
			}
			else if (refParentIB && refParentIB.IsTemperatureVisible())
			{
				tempDiff = Math.AbsFloat(delta * GameConstants.TEMPERATURE_RATE_COOLING_INSIDE);
				tempDistance = Math.AbsFloat(GetTemperature() - refParentIB.GetTemperature());
				if (tempDiff * 2 > tempDistance) {
					tempDiff = tempDistance / 2;
				}
				// balance temperatures of items containing each other
				// TODO: Take into consideration mass of the item.
				if (GetTemperature() > refParentIB.GetTemperature()) {
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
				tempDistance =  Math.AbsFloat(GetTemperature() - envTemp);
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