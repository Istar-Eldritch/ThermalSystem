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

    override bool Post_SetupAction(ActionData action_data)
    {
        return super.Post_SetupAction(action_data) && !IsBlocked(action_data.m_Player, action_data.m_Target, action_data.m_MainItem);
    }

}