modded class ItemActionsWidget
{

    override protected void OnWidgetScriptInit(Widget w)
    {
        super.OnWidgetScriptInit(w);

        array<string> actionTypes = new array<string>;
        actionTypes.Insert("ia_interact");
        actionTypes.Insert("ia_continuous_interact");
        actionTypes.Insert("ia_single");
        actionTypes.Insert("ia_continuous");

        foreach (string action : actionTypes)
        {
            Widget existingIcon = m_Root.FindAnyWidget(action + "_btn_icon");
            Widget blockedIconWidget = ImageWidget.Cast(GetGame().GetWorkspace().CreateWidgets("IE/ThermalSystem/assets/layouts/ie_thermalsystem_snowflake_icon.layout", existingIcon.GetParent()));
			blockedIconWidget.SetName(action + "_btn_icon_frozen_blocked");
			blockedIconWidget.Show(false);

            float x;
            float y;
            existingIcon.GetScreenPos(x, y);
            blockedIconWidget.SetScreenPos(x, y);
            float width;
            float height;
            existingIcon.GetScreenSize(width, height);
            blockedIconWidget.SetScreenSize(width, height);
        }
    }

    override protected void SetActionWidget(ActionBase action, string descText, string actionWidget, string descWidget)
    {
        Widget widget = m_Root.FindAnyWidget(actionWidget);

        if (action && (!action.HasTarget() || (m_Player && m_Player.GetCommand_Vehicle())))
        {
	        TextWidget actionName = TextWidget.Cast(widget.FindAnyWidget(descWidget));
	        Widget actionIcon = widget.FindAnyWidget(actionWidget + "_btn_icon");
			Widget frozenIcon = actionIcon.GetParent().FindAnyWidget(actionWidget + "_btn_icon_frozen_blocked");
			frozenIcon.Show(false);
			string blockedIconId = action.GetBlockedIcon(m_Player, null, ItemBase.Cast(m_EntityInHands));
			Widget blockedIconWidget;
			switch (blockedIconId)
			{
				case "btn_icon_frozen_blocked":
					blockedIconWidget = frozenIcon;
					break;
			}

            bool isBlocked = action.IsBlocked(m_Player, null, ItemBase.Cast(m_EntityInHands));

            if (!isBlocked && action.GetInput().GetInputType() == ActionInputType.AIT_CONTINUOUS)
            {
                descText = descText + " " + "#action_target_cursor_hold";
                actionName.SetText(descText);
                actionIcon.Show(true);
            }
            else
            {
                if (isBlocked)
                {
                    action.GetBlockedText(m_Player, null, ItemBase.Cast(m_EntityInHands));
                    actionName.SetText(action.GetBlockedText(m_Player, null, ItemBase.Cast(m_EntityInHands)));
					actionIcon.Show(false);
                    if (blockedIconWidget)
                    {
                        blockedIconWidget.Show(true);
                    }
                }
                else
                {
                    actionIcon.Show(true);
                    actionName.SetText(descText);
					if (blockedIconWidget)
					{
						blockedIconWidget.Show(false);
					}
                }
            }

            widget.Show(true);
        }
        else
        {
            widget.Show(false);
        }
    }
}