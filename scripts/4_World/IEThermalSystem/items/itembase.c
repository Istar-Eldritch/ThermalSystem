modded class ItemBase
{
	float m_HeatCapacity;
	float m_ThermalEnergy;
	float m_ThermalConductivity;
	float m_Area;
	float m_Thickness;
	bool m_AffectsPlayerComfort;
	float m_ItemWeight;

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
	
	bool CanAffectPlayerComfort()
	{
		return GetThermalSystemConfig().environment.items_affect_player_temperature || CanHaveTemperature() && m_AffectsPlayerComfort;
	}

	override void OnCEUpdate()
	{
		super.OnCEUpdate();
		if (IsUniversalTemperatureSource())
		{
			auto source = GetUniversalTemperatureSource();
			float sourcetemp = source.GetTemperature();
			vector sourcepos = source.GetPosition();
			float sourcefullrange = source.GetFullRange();
			float sourcemaxrange = source.GetMaxRange();
			array<Object> nearestObjects = new array<Object>;
			GetGame().GetObjectsAtPosition(GetPosition(), GameConstants.ENVIRO_TEMP_SOURCES_LOOKUP_RADIUS, nearestObjects, null);

			foreach (Object nearestObject : nearestObjects)
			{
				ItemBase item = ItemBase.Cast(nearestObject);
				if (item != null && item.IECanHaveTemperature() && item != this)
				{
					float distance = Math.Max(vector.Distance(item.GetPosition(), sourcepos), 0.1);
					float sourceTemp = 0;
					if (distance > sourcefullrange)
					{
						float distFactor = Math.Max(1 - (distance / sourcemaxrange), 0.0);
						sourceTemp = sourcetemp * distFactor;
					}
					else
					{
						sourceTemp = sourcetemp;	
					}

					if (item.GetTemperature() < sourceTemp)
					{
						float distanceTemp = Math.AbsFloat(item.GetTemperature() - sourceTemp);
						float thermalEnergy = Math.AbsFloat(m_ElapsedSinceLastUpdate * item.GetThermalEnergyTransferRatio()) * distanceTemp;
						item.AddThermalEnergy(thermalEnergy);
					}
				}
			}
		}
	}

	override void InitItemVariables()
	{
		super.InitItemVariables();
		m_VarTemperatureMin = -273;
		m_VarTemperatureMax = 10000;
		m_HeatCapacity = GetHeatCapacity();
		m_ItemWeight = GetSingleInventoryItemWeightEx();
		UpdateNetSyncVariableFloat("m_VarTemperature", GetTemperatureMin(), GetTemperatureMax());
		if (CanHaveTemperature() && GetGame().IsServer())
		{
			Mission mission = GetGame().GetMission();
			if (mission && mission.GetWorldData())
			{
				auto temperature = mission.GetWorldData().GetBaseEnvTemperature();
				SetTemperature(temperature);
			}
			auto config = GetThermalSystemConfig();
			foreach(auto cls: config.forced_affects_comfort)
			{
				if (GetGame().IsKindOf(GetType(), cls))
				{
					m_AffectsPlayerComfort = true;
					break;
				}
			}
		}
	}

	override float GetWeightSpecialized(bool forceRecalc = false)
	{
		float temp = GetTemperature();
		float weight = super.GetWeightSpecialized(forceRecalc);
		float special = GetInventoryAndCargoWeight();//cargo and attachment weight
		m_ItemWeight = weight - special;
		SetTemperature(temp);
		return weight;
	}

	//Calculates weight of single item without attachments and cargo
	override float GetSingleInventoryItemWeightEx()
	{
		if (m_ItemWeight)
		{
			return m_ItemWeight;
		}
		return super.GetSingleInventoryItemWeightEx();
	}
	
	override void SetTemperature(float value, bool allow_client = false)
	{
		super.SetTemperature(value, allow_client);
		m_ThermalEnergy = CalculateThermalEnergy(m_VarTemperature, m_ItemWeight);
	}
	
	//----------------------------------------------------------------
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		bool success = super.OnStoreLoad(ctx, version);
		if (success) {
			m_ThermalEnergy = CalculateThermalEnergy(m_VarTemperature, GetSingleInventoryItemWeightEx());
		}
		return success;
	}
	
	void AddThermalEnergy(float energy)
	{
		m_ThermalEnergy += energy;
		ReCalculateTemperature(m_ThermalEnergy);	
	}
	
	float CalculateThermalEnergy(float temperature, float weight)
	{
		return (weight / 1000) * (temperature + 273) * GetHeatCapacity();
	}
	
	float GetThermalEnergy()
	{
		return m_ThermalEnergy;
	}

	// Unfortunatelly this also recalculates the internal weight of the item.
	// The implementation offsets the mass change and applies the temperature to the item.
	void ReCalculateTemperature(float thermalEnergy)
	{
		float thermalEnergyDiff = 0;
		if (m_WeightDirty)
		{
			float oldTemperature = GetTemperature();
			float tempThermalEnergy = CalculateThermalEnergy(oldTemperature, m_ItemWeight);
			thermalEnergyDiff = tempThermalEnergy - m_ThermalEnergy;
		}
		// This recalculates the weight of the item with internal mutability.
		float weight = GetSingleInventoryItemWeightEx();
		float newTemperature = ((thermalEnergy + thermalEnergyDiff) / (GetHeatCapacity() * (weight / 1000))) - 273;
		SetTemperature(newTemperature);
	}

	float GetHeatCapacity()
	{
		if (!m_HeatCapacity)
		{
			auto config = GetThermalSystemConfig();
			foreach(auto hc: config.heat_capacities)
			{
				if (GetGame().IsKindOf(GetType(), hc.item))
				{
					m_HeatCapacity = hc.heat_capacity;
					return m_HeatCapacity;
				}
			}
			m_HeatCapacity = 1.012;	
		}
		return m_HeatCapacity;
	}

	float GetThermalEnergyTransferRatio()
	{
		auto config = GetThermalSystemConfig();
		return (GetThermalConductivity() * GetArea() * config.environment.thermal_conductivity_rate) / (GetThickness() * 1000));
	}
	
	float GetThermalConductivity()
	{
		if (!m_ThermalConductivity)
		{
			auto config = GetThermalSystemConfig();
			foreach(auto hc: config.heat_capacities)
			{
				if (GetGame().IsKindOf(GetType(), hc.item))
				{
					m_ThermalConductivity = hc.thermal_conductivity;
					return m_ThermalConductivity;
				}
			}
			m_ThermalConductivity = 0.02535;	
		}
		return m_ThermalConductivity;
	}
	
	float GetArea()
	{
		if (!m_Area)
		{
			vector min = GetMemoryPointPos("boundingbox_min");
			vector max = GetMemoryPointPos("boundingbox_max");
			float a = Math.AbsFloat(min[0] - max[0]);
			float b = Math.AbsFloat(min[1] - max[1]);
			float c = Math.AbsFloat(min[2] - max[2]);
			m_Area = 2*(a*b+a*c+b*c);
			if (m_Area < 0.1)
				m_Area = 0.1;
		}
		
		return m_Area;
	}
	
	float GetThickness()
	{
		if (!m_Thickness)
		{
			vector min = GetMemoryPointPos("boundingbox_min");
			vector max = GetMemoryPointPos("boundingbox_max");
			float a = Math.AbsFloat(min[0] - max[0]);
			float b = Math.AbsFloat(min[1] - max[1]);
			float c = Math.AbsFloat(min[2] - max[2]);
			m_Thickness = Math.SqrFloat(Math.Pow(a, 2) + Math.Pow(b, 2) + Math.Pow(c, 2));
			if (m_Thickness < 0.05)
				m_Thickness = 0.05;
		}
		return m_Thickness;
	}

	override void ProcessItemTemperature(float delta, bool hasParent, bool hasRootAsPlayer, ItemBase refParentIB)
	{
		float tempDistance = 0;
		float transferRatio = GetThermalEnergyTransferRatio();
		float tempDiff = Math.AbsFloat(delta * transferRatio);
		if (!hasRootAsPlayer && !IsFireplace())
		{
			if (refParentIB && refParentIB.IECanHaveTemperature())
			{
				float parentTemperature = refParentIB.GetTemperature();
				tempDistance = Math.AbsFloat(GetTemperature() - parentTemperature);
				float parentDiff = refParentIB.GetThermalEnergyTransferRatio() * delta * tempDistance;
				tempDiff *= tempDistance;
				// balance temperatures of items containing each other
				if (GetTemperature() > parentTemperature)
				{
					tempDiff *= -1;
					parentDiff *= -1;
				}

				AddThermalEnergy(tempDiff);
				if (!refParentIB.IsFireplace())
				{
					refParentIB.AddThermalEnergy(parentDiff * -1);
				}
			}
			else
			{
				float envTemp = GetGame().GetMission().GetWorldData().GetBaseEnvTemperature();

				tempDistance = Math.AbsFloat(GetTemperature() - envTemp);
				tempDiff *= tempDistance;
				if (GetTemperature() > envTemp)
					tempDiff = tempDiff * -1;
				AddThermalEnergy(tempDiff);
			}
		}
	}
}