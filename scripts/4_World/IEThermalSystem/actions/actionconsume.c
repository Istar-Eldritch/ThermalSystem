
modded class ActionConsume
{
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
};