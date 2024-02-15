
modded class ActionConsume
{
    override void Start(ActionData action_data)
    {
        super.Start(action_data);
    }

    override bool IsBlocked(PlayerBase player, ActionTarget target, ItemBase item)
    {
        Edible_Base edible = Edible_Base.Cast(item);
        return edible.GetTemperature() < 0 && !edible.CanBeConsumedFrozen();
    }

    override string GetBlockedText(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "Can't be consumed frozen";
    }

    override string GetBlockedIcon(PlayerBase player, ActionTarget target, ItemBase item)
    {
        return "ie_thermalsystem_snowflake";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        auto edible = Edible_Base.Cast(item);
        return super.ActionCondition(player, target, item);
    }
};