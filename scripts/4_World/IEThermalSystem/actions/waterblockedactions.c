modded class ActionDrainLiquid
{
    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        ItemBase targetItem = ItemBase.Cast(target.GetObject());
        return targetItem != null && targetItem.IsFrozen();
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
            action_data.m_MainItem.SetTemperature(targetItem.GetTemperature());
        }
	}
};

modded class ActionEmptyBottleBase
{
    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IsFrozen();
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't empty while frozen";
    }

    override string GetBlockedIcon(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "btn_icon_frozen_blocked";
    }
};

modded class ActionExtinguishFireplaceByLiquid
{
    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IsFrozen();
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't extinguish while frozen";
    }

    override string GetBlockedIcon(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "btn_icon_frozen_blocked";
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
    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IsFrozen();
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't fill while frozen";
    }

    override string GetBlockedIcon(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "btn_icon_frozen_blocked";
    }
};

modded class ActionWaterPlant
{
    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IsFrozen();
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't water while frozen";
    }

    override string GetBlockedIcon(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "btn_icon_frozen_blocked";
    }
};

modded class ActionWaterGardenSlot
{
    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IsFrozen();
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't water while frozen";
    }

    override string GetBlockedIcon(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "btn_icon_frozen_blocked";
    }
};

modded class ActionForceDrink
{
    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IsFrozen();
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't force drink while frozen";
    }

    override string GetBlockedIcon(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "btn_icon_frozen_blocked";
    }
};

modded class ActionPourLiquid
{
    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IsFrozen();
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
};

modded class ActionWashHandsItemContinuous
{
    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IsFrozen();
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't wash hands while frozen";
    }

    override string GetBlockedIcon(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "btn_icon_frozen_blocked";
    }
};