

modded class ActionTargetsCursor
{
    override protected void OnWidgetScriptInit(Widget w)
    {
        super.OnWidgetScriptInit(w);

        array<string> actionTypes = new array<string>;
        actionTypes.Insert("interact");
        actionTypes.Insert("continuous_interact");
        actionTypes.Insert("single");
        actionTypes.Insert("continuous");

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
		
		if (action)
		{
			if (action.HasTarget() && m_AM.GetActionState() < 1) // targeted & action not performing
			{
                TextWidget actionName = TextWidget.Cast(widget.FindAnyWidget(descWidget));
                Widget actionIcon = widget.FindAnyWidget(actionWidget + "_btn_icon");
                Widget frozenIcon = actionIcon.GetParent().FindAnyWidget(actionWidget + "_btn_icon_frozen_blocked");
                frozenIcon.Show(false);
				ActionTarget target;
                string blockedIconId = action.GetBlockedIcon(m_Player, m_Target, m_Player.GetItemInHands());
                Widget blockedIconWidget;
                switch (blockedIconId)
                {
                    case "btn_icon_frozen_blocked":
                        blockedIconWidget = frozenIcon;
                        break;
                }

                bool isBlocked = action.IsBlocked(m_Player, m_Target, m_Player.GetItemInHands());
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
                        action.GetBlockedText(m_Player, m_Target, m_Player.GetItemInHands());
                        actionName.SetText(action.GetBlockedText(m_Player, m_Target, m_Player.GetItemInHands()));
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
				
				int x, y;
				actionName.GetTextSize(x, y);
				if (x > m_MaxWidthChild);
					m_MaxWidthChild = x;
			}
			else
			{
				widget.Show(false);
			}
		}
		else
		{
			widget.Show(false);
		}
	}
}