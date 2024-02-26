modded class ActionFishingNewCB
{
    override void HandleFishingResultSuccess()
	{
		if (!GetGame().IsMultiplayer() || GetGame().IsServer())
		{
			ItemBase fish;

			if (!m_ActionDataFishing.m_Bait)
				m_ActionDataFishing.InitBait(ItemBase.Cast(m_ActionDataFishing.m_MainItem.FindAttachmentBySlotName("Hook")));
			
			if (!m_ActionDataFishing.IsBaitEmptyHook())
			{
				m_ActionDataFishing.m_Bait.AddHealth(-m_ActionDataFishing.FISHING_DAMAGE);
				MiscGameplayFunctions.TurnItemIntoItem(m_ActionDataFishing.m_Bait,m_ActionDataFishing.m_Bait.ConfigGetString("hookType"),m_ActionDataFishing.m_Player);
			}
			else
			{
				m_ActionDataFishing.m_Bait.AddHealth(-m_ActionDataFishing.FISHING_DAMAGE);
			}
			
			float rnd = Math.RandomFloatInclusive(0.0, 1.0);
			if (rnd > m_ActionDataFishing.FISHING_GARBAGE_CHANCE)
			{
				if (m_ActionDataFishing.m_IsSurfaceSea)
					fish = ItemBase.Cast(GetGame().CreateObjectEx("Mackerel",m_ActionDataFishing.m_Player.GetPosition(), ECE_PLACE_ON_SURFACE));
				else
					fish = ItemBase.Cast(GetGame().CreateObjectEx("Carp",m_ActionDataFishing.m_Player.GetPosition(), ECE_PLACE_ON_SURFACE));
			}
			else
			{
				if ( !m_ActionDataFishing.m_IsSurfaceSea )
				{
					string junkType = m_JunkTypes.Get(Math.RandomInt(0, m_JunkTypes.Count()));
					fish = ItemBase.Cast(GetGame().CreateObjectEx(junkType, m_ActionDataFishing.m_Player.GetPosition(), ECE_PLACE_ON_SURFACE));
					fish.SetHealth("", "Health", fish.GetMaxHealth("", "Health") * 0.1);
				}
			}
			
			if (fish)
			{
				//Print("---Caught something: " + fish + "---");
				fish.SetWet(0.3);
				if (fish.HasQuantity())
				{
					float coef = Math.RandomFloatInclusive(0.5, 1.0);
					float item_quantity = fish.GetQuantityMax() * coef;
					item_quantity = Math.Round(item_quantity);
					fish.SetQuantity( item_quantity );
					fish.InsertAgent(eAgents.CHOLERA);
				}
                auto config = GetThermalSystemConfig();
                fish.SetTemperature(config.fishing_item_temperature);
			}
			
			m_ActionDataFishing.m_MainItem.AddHealth(-m_ActionDataFishing.FISHING_DAMAGE);
		}
	}
}