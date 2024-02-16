modded class Environment
{
	// float m_LogTime = 0;

	// override void Update(float pDelta)
	// {
	// 	m_LogTime += pDelta;
	// 	if ( m_LogTime >= 10 )
	// 	{
	// 		m_LogTime = 0;
	// 		Print("\n\n" + GetDebugMessage());
	// 	}
	// 	super.Update(pDelta);
	// }
	
	// Calculates and return temperature of environment
	override protected float GetEnvironmentTemperature()
	{
		float temperature;
		temperature = g_Game.GetMission().GetWorldData().GetBaseEnvTemperature();
		temperature += Math.AbsFloat(temperature * m_Clouds * GameConstants.ENVIRO_CLOUDS_TEMP_EFFECT);
		float player_comfort_temp_low = GetThermalSystemConfig().environment.player_comfort_temp_low;
		float player_comfort_temp_hi = GetThermalSystemConfig().environment.player_comfort_temp_hi;

		if (IsWaterContact())
		{
			temperature -= Math.AbsFloat(temperature * GameConstants.ENVIRO_WATER_TEMPERATURE_COEF);
		}

		if (IsInsideBuilding() || m_IsUnderRoofBuilding)
		{
			if (temperature < player_comfort_temp_low)
				temperature += Math.AbsFloat(temperature * GameConstants.ENVIRO_TEMPERATURE_INSIDE_COEF);
			if (temperature > player_comfort_temp_hi)
				temperature -= Math.AbsFloat(temperature * GameConstants.ENVIRO_TEMPERATURE_INSIDE_COEF);
		}
		else if (IsInsideVehicle())
		{
			if (temperature < player_comfort_temp_low)
				temperature += Math.AbsFloat(temperature * GameConstants.ENVIRO_TEMPERATURE_INSIDE_VEHICLE_COEF);
			if (temperature > player_comfort_temp_hi)
				temperature -= Math.AbsFloat(temperature * GameConstants.ENVIRO_TEMPERATURE_INSIDE_VEHICLE_COEF);
		}
		else if (IsUnderRoof() && !m_IsUnderRoofBuilding)
		{
			if (temperature < player_comfort_temp_low)
				temperature += Math.AbsFloat(temperature * GameConstants.ENVIRO_TEMPERATURE_UNDERROOF_COEF);
			if (temperature > player_comfort_temp_hi)
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
		float tempsource = Math.AbsFloat(m_UTSAverageTemperature);
		if ( tempsource > temperature + 0.001)
		{
			temperature += m_UTSAverageTemperature;
		}

		if ( tempsource < temperature - 0.001)
		{
			temperature -= m_UTSAverageTemperature;
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
					distanceTemp = Math.AbsFloat(pItem.GetTemperature() - GameConstants.ENVIRO_PLAYER_COMFORT_TEMP);
					if (distanceTemp < diffTemp)
						diffTemp = distanceTemp;

					if (pItem.GetTemperature() > GameConstants.ENVIRO_PLAYER_COMFORT_TEMP)
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
				if (parentItem != null && parentItem.IECanHaveTemperature()) // Parent
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
					distanceTemp = Math.AbsFloat(pItem.GetTemperature() - GameConstants.ENVIRO_PLAYER_COMFORT_TEMP);
					if (distanceTemp < diffTemp)
						diffTemp = distanceTemp;

					if (pItem.GetTemperature() > GameConstants.ENVIRO_PLAYER_COMFORT_TEMP)
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
	
	override protected void ProcessItemsHeat()
	{
		float hcHead, hcBody, hcFeet;	//! Heat Comfort
		float hHead, hBody, hFeet;		//! Heat (from items);
		
		float heatComfortAvg;
		float heatAvg;

		BodyPartHeatProperties(m_HeadParts, GameConstants.ENVIRO_HEATCOMFORT_HEADPARTS_WEIGHT, hcHead, hHead);
		BodyPartHeatProperties(m_BodyParts, GameConstants.ENVIRO_HEATCOMFORT_BODYPARTS_WEIGHT, hcBody, hBody);
		BodyPartHeatProperties(m_FeetParts, GameConstants.ENVIRO_HEATCOMFORT_FEETPARTS_WEIGHT, hcFeet, hFeet);

		heatComfortAvg = (hcHead + hcBody + hcFeet) / 3;
		heatAvg = (hHead + hBody + hFeet) / 3;
		
		// heat buffer
		float applicableHB = 0.0;
		if (m_UTSAverageTemperature < GameConstants.ENVIRO_PLAYER_COMFORT_TEMP)
		{
			applicableHB = m_Player.GetStatHeatBuffer().Get() / 30.0;
			if (applicableHB > 0.0)
			{
				if (m_HeatBufferTimer > 1.0)
				{
					m_Player.GetStatHeatBuffer().Add(Math.Min(EnvTempToCoef(m_EnvironmentTemperature), -0.1) * GameConstants.ENVIRO_PLAYER_HEATBUFFER_DECREASE);
				}
				else
				{
					m_HeatBufferTimer += GameConstants.ENVIRO_PLAYER_HEATBUFFER_TICK;
				}
			}
			else
			{
				m_HeatBufferTimer = 0.0;
			}			
		}
		else
		{
			applicableHB = m_Player.GetStatHeatBuffer().Get() / 30.0;
			if (m_HeatComfort > PlayerConstants.THRESHOLD_HEAT_COMFORT_MINUS_WARNING)
			{
				m_Player.GetStatHeatBuffer().Add(GameConstants.ENVIRO_PLAYER_HEATBUFFER_INCREASE);
				m_HeatBufferTimer = 0.0;
			}
			else
			{
				m_HeatBufferTimer = 0.0;
			}
		}
		
		m_HeatComfort = (heatComfortAvg + heatAvg + (GetPlayerHeat() / 100)) + EnvTempToCoef(m_EnvironmentTemperature);
		if ((m_HeatComfort + applicableHB) < (PlayerConstants.THRESHOLD_HEAT_COMFORT_PLUS_WARNING - 0.01))
		{
			m_HeatComfort += applicableHB;
		}
		else
		{
			if (m_HeatComfort <= (PlayerConstants.THRESHOLD_HEAT_COMFORT_PLUS_WARNING - 0.01))
			{
				m_HeatComfort = PlayerConstants.THRESHOLD_HEAT_COMFORT_PLUS_WARNING - 0.01;
			}
		}

		m_HeatComfort = Math.Clamp(m_HeatComfort, m_Player.GetStatHeatComfort().GetMin(), m_Player.GetStatHeatComfort().GetMax());
		
		m_Player.GetStatHeatComfort().Set(m_HeatComfort);
	}
	
	override protected void BodyPartHeatProperties(array<int> pBodyPartIds, float pCoef, out float pHeatComfort, out float pHeat)
	{
		int attCount;
		
		EntityAI attachment;
		ItemBase item;
		
		pHeatComfort = -1;
		attCount = m_Player.GetInventory().AttachmentCount();

		for (int attIdx = 0; attIdx < attCount; attIdx++)
		{
			attachment = m_Player.GetInventory().GetAttachmentFromIndex(attIdx);
			if (attachment.IsClothing())
			{
				item = ItemBase.Cast(attachment);
				int attachmentSlot = attachment.GetInventory().GetSlotId(0);

				//! go through all body parts we've defined for that zone (ex.: head, body, feet)
				for (int i = 0; i < pBodyPartIds.Count(); i++)
				{
					if (attachmentSlot == pBodyPartIds.Get(i))
					{
						float heatIsoMult = 1.0;
						if (attachmentSlot == InventorySlots.VEST)
						{
							heatIsoMult = GameConstants.ENVIRO_HEATISOLATION_VEST_WEIGHT;
						}

						if (attachmentSlot == InventorySlots.BACK)
						{
							heatIsoMult = GameConstants.ENVIRO_HEATISOLATION_BACK_WEIGHT;
						}

						pHeatComfort += heatIsoMult * MiscGameplayFunctions.GetCurrentItemHeatIsolation(item);
						if (item.IECanHaveTemperature())
						{
							pHeat += ItemTempToCoef(item.GetTemperature());
						}
						// go through any attachments and cargo (only current level, ignore nested containers - they isolate)
						int inAttCount = item.GetInventory().AttachmentCount();
						if (inAttCount > 0 && attachmentSlot != InventorySlots.BACK)
						{
							for (int inAttIdx = 0; inAttIdx < inAttCount; inAttIdx++)
							{
								EntityAI inAttachment = item.GetInventory().GetAttachmentFromIndex(inAttIdx);
								ItemBase itemAtt = ItemBase.Cast(inAttachment);
								if (itemAtt != null && itemAtt.IECanHaveTemperature())
								{
									pHeat += ItemTempToCoef(itemAtt.GetTemperature());
								}
							}
						}
						if (item.GetInventory().GetCargo() && attachmentSlot != InventorySlots.BACK )
						{
							int inItemCount = item.GetInventory().GetCargo().GetItemCount();
							
							for (int j = 0; j < inItemCount; j++)
							{
								ItemBase inItem;
								if (Class.CastTo(inItem, item.GetInventory().GetCargo().GetItem(j)) && inItem.IECanHaveTemperature())
								{
									pHeat += ItemTempToCoef(inItem.GetTemperature());
								}
							}
						}
					}
				}
			}
		}

		pHeatComfort = (pHeatComfort / pBodyPartIds.Count()) * pCoef;
		pHeat = pHeat * pCoef;
	}
	
	protected float ItemTempToCoef(float pTemp)
	{
		float player_comfort_temp_low = GetThermalSystemConfig().environment.player_comfort_temp_low;
		float player_comfort_temp_hi = GetThermalSystemConfig().environment.player_comfort_temp_hi;
		float item_temp_effect_on_player = GetThermalSystemConfig().environment.item_temp_effect_on_player;
		if (pTemp > player_comfort_temp_low && pTemp < player_comfort_temp_hi)
			return 0;
		float coef = (pTemp - GameConstants.ENVIRO_PLAYER_COMFORT_TEMP) / item_temp_effect_on_player;
		if (coef > 1)
			return 1;
		if (coef < -1)
			return -1;
		return coef;
	}
}