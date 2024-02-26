
modded class ActionConsume
{
    float m_TempMem;

    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        Edible_Base edible = Edible_Base.Cast(item);
        return edible.IECanHaveTemperature() && edible.GetTemperature() < 0 && !edible.CanBeConsumedFrozen();
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't consume while frozen";
    }

    override string GetBlockedIcon(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "btn_icon_frozen_blocked";
    }

	override void OnStartAnimationLoop( ActionData action_data )
	{
        super.OnStartAnimationLoop(action_data);
		if (GetGame().IsServer() )
		{
			Edible_Base edible = Edible_Base.Cast( action_data.m_MainItem );
            if (edible)
            {
                m_TempMem = edible.GetTemperature();
            }
		}
	}

	override void OnEndAnimationLoop( ActionData action_data )
	{
        super.OnEndAnimationLoop(action_data);
		if (GetGame().IsServer() )
		{
			Edible_Base edible = Edible_Base.Cast( action_data.m_MainItem );
            if (edible)
            {
                edible.SetTemperature(m_TempMem);
            }
		}
	}
};