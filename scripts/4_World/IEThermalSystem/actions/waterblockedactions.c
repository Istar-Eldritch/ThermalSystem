modded class ActionDrainLiquid
{
    float m_TempMem;

    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        ItemBase targetItem = ItemBase.Cast(target.GetObject());
        return targetItem != null && targetItem.IECanHaveTemperature() && targetItem.GetTemperature() < 0 && targetItem.m_VarLiquidType == LIQUID_WATER && GetThermalSystemConfig().water_freezes;
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't drain while frozen";
    }

    override string GetBlockedIcon(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "btn_icon_frozen_blocked";
    }

	override protected void OnExecuteServer( ActionData action_data )
	{
        ItemBase targetItem = ItemBase.Cast(action_data.m_Target.GetObject());
		action_data.m_MainItem.GetTemperature();
        if(targetItem.IECanHaveTemperature() && action_data.m_MainItem.IECanHaveTemperature())
        {
            targetItem.SetTemperature(action_data.m_MainItem.GetTemperature());
        }
	}


	override void OnStartAnimationLoop( ActionData action_data )
	{
        super.OnStartAnimationLoop(action_data);
		if (GetGame().IsServer() )
		{
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                m_TempMem = bottle.GetTemperature();
            }
		}
	}

	override void OnEndAnimationLoop( ActionData action_data )
	{
        super.OnEndAnimationLoop(action_data);
		if (GetGame().IsServer() )
		{
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                bottle.SetTemperature(m_TempMem);
            }
		}
	}
};

modded class ActionEmptyBottleBase
{
    float m_TempMem;

    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IECanHaveTemperature() && item.GetTemperature() < 0 && item.m_VarLiquidType == LIQUID_WATER && GetThermalSystemConfig().water_freezes;
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't empty while frozen";
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
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                m_TempMem = bottle.GetTemperature();
            }
		}
	}

	override void OnEndAnimationLoop( ActionData action_data )
	{
        super.OnEndAnimationLoop(action_data);
		if (GetGame().IsServer() )
		{
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                bottle.SetTemperature(m_TempMem);
            }
		}
	}
};

modded class ActionExtinguishFireplaceByLiquid
{
    float m_TempMem;

    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IECanHaveTemperature() && item.GetTemperature() < 0 && item.m_VarLiquidType == LIQUID_WATER && GetThermalSystemConfig().water_freezes;
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't extinguish while frozen";
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
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                m_TempMem = bottle.GetTemperature();
            }
		}
	}

	override void OnEndAnimationLoop( ActionData action_data )
	{
        super.OnEndAnimationLoop(action_data);
		if (GetGame().IsServer() )
		{
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                bottle.SetTemperature(m_TempMem);
            }
		}
	}
};

modded class ActionFillBottleBase
{
	override void OnEndAnimationLoop( ActionData action_data )
	{
        super.OnEndAnimationLoop(action_data);
		if (GetGame().IsServer() )
		{
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                bottle.SetTemperature(GetThermalSystemConfig().water_well_temperature);
            }
		}
	}
};

modded class ActionFillCoolant
{
    float m_TempMem;

    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IECanHaveTemperature() && item.GetTemperature() < 0 && item.m_VarLiquidType == LIQUID_WATER && GetThermalSystemConfig().water_freezes;
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't fill while frozen";
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
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                m_TempMem = bottle.GetTemperature();
            }
		}
	}

	override void OnEndAnimationLoop( ActionData action_data )
	{
        super.OnEndAnimationLoop(action_data);
		if (GetGame().IsServer() )
		{
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                bottle.SetTemperature(m_TempMem);
            }
		}
	}
};

modded class ActionWaterPlant
{
    float m_TempMem;

    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IECanHaveTemperature() && item.GetTemperature() < 0 && item.m_VarLiquidType == LIQUID_WATER && GetThermalSystemConfig().water_freezes;
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't water while frozen";
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
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                m_TempMem = bottle.GetTemperature();
            }
		}
	}

	override void OnEndAnimationLoop( ActionData action_data )
	{
        super.OnEndAnimationLoop(action_data);
		if (GetGame().IsServer() )
		{
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                bottle.SetTemperature(m_TempMem);
            }
		}
	}
};

modded class ActionWaterGardenSlot
{
    float m_TempMem;

    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IECanHaveTemperature() && item.GetTemperature() < 0 && item.m_VarLiquidType == LIQUID_WATER && GetThermalSystemConfig().water_freezes;
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't water while frozen";
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
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                m_TempMem = bottle.GetTemperature();
            }
		}
	}

	override void OnEndAnimationLoop( ActionData action_data )
	{
        super.OnEndAnimationLoop(action_data);
		if (GetGame().IsServer() )
		{
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                bottle.SetTemperature(m_TempMem);
            }
		}
	}
};

modded class ActionForceDrink
{
    float m_TempMem;

    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IECanHaveTemperature() && item.GetTemperature() < 0 && item.m_VarLiquidType == LIQUID_WATER && GetThermalSystemConfig().water_freezes;
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't force drink while frozen";
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
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                m_TempMem = bottle.GetTemperature();
            }
		}
	}

	override void OnEndAnimationLoop( ActionData action_data )
	{
        super.OnEndAnimationLoop(action_data);
		if (GetGame().IsServer() )
		{
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                bottle.SetTemperature(m_TempMem);
            }
		}
	}
};

modded class ActionPourLiquid
{
    float m_TempMem;

    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IECanHaveTemperature() && item.GetTemperature() < 0 && item.m_VarLiquidType == LIQUID_WATER && GetThermalSystemConfig().water_freezes;
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't pour while frozen";
    }

    override string GetBlockedIcon(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "btn_icon_frozen_blocked";
    }

	override protected void OnExecuteServer( ActionData action_data )
	{
        ItemBase targetItem = ItemBase.Cast(action_data.m_Target.GetObject());
        if(targetItem.IECanHaveTemperature() && action_data.m_MainItem.IECanHaveTemperature())
        {
            targetItem.SetTemperature(action_data.m_MainItem.GetTemperature());
        }
	}

	override void OnStartAnimationLoop( ActionData action_data )
	{
        super.OnStartAnimationLoop(action_data);
		if (GetGame().IsServer() )
		{
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                m_TempMem = bottle.GetTemperature();
            }
		}
	}

	override void OnEndAnimationLoop( ActionData action_data )
	{
        super.OnEndAnimationLoop(action_data);
		if (GetGame().IsServer() )
		{
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                bottle.SetTemperature(m_TempMem);
            }
		}
	}
};

modded class ActionWashHandsItemContinuous
{
    float m_TempMem;

    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IECanHaveTemperature() && item.GetTemperature() < 0 && item.m_VarLiquidType == LIQUID_WATER && GetThermalSystemConfig().water_freezes;
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't wash hands while frozen";
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
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                m_TempMem = bottle.GetTemperature();
            }
		}
	}

	override void OnEndAnimationLoop( ActionData action_data )
	{
        super.OnEndAnimationLoop(action_data);
		if (GetGame().IsServer() )
		{
			Bottle_Base bottle = Bottle_Base.Cast( action_data.m_MainItem );
            if (bottle)
            {
                bottle.SetTemperature(m_TempMem);
            }
		}
	}
};