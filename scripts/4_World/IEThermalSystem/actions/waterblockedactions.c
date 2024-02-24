modded class ActionDrainLiquid
{
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
        if(targetItem.IECanHaveTemperature() && action_data.m_MainItem.IECanHaveTemperature())
        {
            targetItem.SetTemperature(action_data.m_MainItem.GetTemperature());
        }
	}
};

modded class ActionEmptyBottleBase
{
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
};

modded class ActionExtinguishFireplaceByLiquid
{
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

	override protected void OnExecuteServer( ActionData action_data )
	{
        ItemBase targetItem = ItemBase.Cast(action_data.m_Target.GetObject());
        if(targetItem.IECanHaveTemperature() && action_data.m_MainItem.IECanHaveTemperature())
        {
            targetItem.SetTemperature(action_data.m_MainItem.GetTemperature());
        }
	}
};

modded class ActionFillBottleBase
{

	override protected void OnExecuteServer( ActionData action_data )
	{
        ItemBase item = action_data.m_MainItem;
        if(item.IECanHaveTemperature() && item.m_VarLiquidType == LIQUID_WATER)
        {
            item.SetTemperature(GetThermalSystemConfig().water_well_temperature);
        }
	}
};

modded class ActionFillCoolant
{
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
};

modded class ActionWaterPlant
{
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
};

modded class ActionWaterGardenSlot
{
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
};

modded class ActionForceDrink
{
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
};

modded class ActionPourLiquid
{
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
};

modded class ActionWashHandsItemContinuous
{
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
};