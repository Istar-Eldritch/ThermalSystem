
modded class ActionEmptyBottleBase
{
    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return item.IECanHaveTemperature() && item.GetTemperature() < 0 && item.m_VarLiquidType == LIQUID_WATER;
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't empty while frozen";
    }

    override string GetBlockedIcon(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "ie_thermalsystem_snowflake";
    }
};