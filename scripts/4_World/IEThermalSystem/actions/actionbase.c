modded class ActionBase
{
    bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return false;
    }

    string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "";
    }

    string GetBlockedIcon(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "";
    }

    override bool Post_SetupAction( ActionData action_data )
	{
		return !IsBlocked(action_data.m_Player, action_data.m_Target, action_data.m_MainItem);
	}

	override bool Can( PlayerBase player, ActionTarget target, ItemBase item, int condition_mask )
	{
		if ( ( (condition_mask & m_ConditionMask) != condition_mask ) || ( !IsFullBody(player) && !player.IsPlayerInStance(GetStanceMask(player)) ) || player.IsRolling() )
			return false;
		
		if ( HasTarget() )
		{
			if(!FirearmActionBase.Cast(this))
			{
				EntityAI entity = EntityAI.Cast(target.GetObject());
				if ( entity && !target.GetObject().IsMan() )
				{
					Man man = entity.GetHierarchyRootPlayer();
					if ( man && man != player )
						return false;
				}
			}
			
			if ( m_ConditionTarget && !m_ConditionTarget.Can(player, target))
				return false;
		}
		
		if ( m_ConditionItem && !m_ConditionItem.Can(player, item))
			return false;
		
		if ( !ActionCondition(player, target, item) && !IsBlocked(player, target, item) )
			return false;
		
		if ( IsFullBody(player) )
		{
			int stanceIdx = DayZPlayerUtils.ConvertStanceMaskToStanceIdx(GetStanceMask(player));
			if (stanceIdx != -1 && !DayZPlayerUtils.PlayerCanChangeStance(player, stanceIdx ))
				return false;
		}
		
		return true;
	}
}