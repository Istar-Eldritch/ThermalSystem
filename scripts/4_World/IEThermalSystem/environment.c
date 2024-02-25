modded class Environment
{

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
		if ( tempsource > 0 && tempsource > temperature)
		{
			temperature = tempsource;
		}

		return temperature;
	}

	void ApplyTemperatureToItem(ItemBase pItem)
	{
		if (pItem && pItem.IECanHaveTemperature())
		{
			ItemBase parentItem;
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
					}
				}
			}

			float diffTemp = Math.AbsFloat(GameConstants.ENVIRO_TICK_RATE * pItem.GetThermalEnergyTransferRatio());
			float distanceTemp;
			ItemBase itemInHands = m_Player.GetItemInHands();
			if (parentILoc.GetSlot() == InventorySlots.BACK || (itemInHands != null && itemInHands.GetID() == pItem.GetID())) // Items carried on the back shall aproach ambient temperature
			{
				distanceTemp = Math.AbsFloat(pItem.GetTemperature() - GetTemperature());
				diffTemp *= distanceTemp;

				if (pItem.GetTemperature() > GetTemperature())
					diffTemp *= -1;
			}
			else if (parentItem != null && parentItem.IECanHaveTemperature()) // Parent
			{
				distanceTemp = Math.AbsFloat(pItem.GetTemperature() - parentItem.GetTemperature());
				diffTemp *= distanceTemp;
				float parentDiff = parentItem.GetThermalEnergyTransferRatio() * GameConstants.ENVIRO_TICK_RATE * distanceTemp;

				if (pItem.GetTemperature() > parentItem.GetTemperature())
					diffTemp *= -1;
					parentDiff *= -1;
				parentItem.AddThermalEnergy(parentDiff * -1);
			}
			else
			{
				distanceTemp = Math.AbsFloat(pItem.GetTemperature() - GameConstants.ENVIRO_PLAYER_COMFORT_TEMP);
				diffTemp *= distanceTemp;
				if (pItem.GetTemperature() > GameConstants.ENVIRO_PLAYER_COMFORT_TEMP)
					diffTemp = diffTemp * -1;
			}

			pItem.AddThermalEnergy(diffTemp);
		}
	}

	// Temperature is controlled independently of wetness
	override override void ApplyWetnessToItem(ItemBase pItem)
	{
		float beforeTemperature = pItem.GetTemperature();
		super.ApplyWetnessToItem(pItem);
		if (pItem && pItem.IECanHaveTemperature())
		{
			pItem.SetTemperature(beforeTemperature);
		}
	}

	// Temperature is controlled independently of wetness
	override protected void ApplyDrynessToItemEx(ItemBase pItem, EnvironmentDrynessData pDrynessData)
	{
		float beforeTemperature = pItem.GetTemperature();
		super.ApplyDrynessToItemEx(pItem, pDrynessData);
		if (pItem && pItem.IECanHaveTemperature())
		{
			pItem.SetTemperature(beforeTemperature);
		}
	}
	
	override protected void ProcessItemsHeat()
	{
		float hcHead, hcBody, hcFeet;	//! Heat Comfort
		float hHead, hBody, hFeet;		//! Heat (from items);
		
		float heatComfortAvg;
		float heatAvg;

		if (m_Player.GetItemInHands())
		{
			ApplyTemperatureToItem(m_Player.GetItemInHands());
		}

		BodyPartHeatProperties(m_HeadParts, GameConstants.ENVIRO_HEATCOMFORT_HEADPARTS_WEIGHT, hcHead, hHead);
		BodyPartHeatProperties(m_BodyParts, GameConstants.ENVIRO_HEATCOMFORT_BODYPARTS_WEIGHT, hcBody, hBody);
		BodyPartHeatProperties(m_FeetParts, GameConstants.ENVIRO_HEATCOMFORT_FEETPARTS_WEIGHT, hcFeet, hFeet);

		heatComfortAvg = (hcHead + hcBody + hcFeet) / 3;
		heatAvg = (hHead + hBody + hFeet) / 3;
		
		// heat buffer
		float applicableHB = 0.0;
		if (m_UTSAverageTemperature <= 0)
		{
			applicableHB = m_Player.GetStatHeatBuffer().Get() / GameConstants.ENVIRO_PLAYER_COMFORT_TEMP;
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
			applicableHB = m_Player.GetStatHeatBuffer().Get() / GameConstants.ENVIRO_PLAYER_COMFORT_TEMP;
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
							ApplyTemperatureToItem(item);
							pHeat += ItemTempToCoef(item.GetTemperature());
						}
						// go through any attachments and cargo (only current level, ignore nested containers - they isolate)
						int inAttCount = item.GetInventory().AttachmentCount();
						if (inAttCount > 0)
						{
							for (int inAttIdx = 0; inAttIdx < inAttCount; inAttIdx++)
							{
								EntityAI inAttachment = item.GetInventory().GetAttachmentFromIndex(inAttIdx);
								ItemBase itemAtt = ItemBase.Cast(inAttachment);
								if (itemAtt != null && itemAtt.IECanHaveTemperature())
								{
									ApplyTemperatureToItem(itemAtt);
									if (attachmentSlot != InventorySlots.BACK)
									{
										pHeat += ItemTempToCoef(itemAtt.GetTemperature());
									}
								}
							}
						}
						if (item.GetInventory().GetCargo())
						{
							int inItemCount = item.GetInventory().GetCargo().GetItemCount();
							
							for (int j = 0; j < inItemCount; j++)
							{
								ItemBase inItem;
								if (Class.CastTo(inItem, item.GetInventory().GetCargo().GetItem(j)) && inItem.IECanHaveTemperature())
								{
									ApplyTemperatureToItem(inItem);
									if(attachmentSlot != InventorySlots.BACK )
									{
										pHeat += ItemTempToCoef(inItem.GetTemperature());
									}
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