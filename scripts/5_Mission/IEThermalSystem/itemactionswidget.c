modded class ItemActionsWidget
{

    ref array<ref Widget> m_BlockingIcons = new array<ref Widget>;
    ref array<string> m_ActionTypes = new array<string>;

    override protected void OnWidgetScriptInit(Widget w)
    {
        super.OnWidgetScriptInit(w);

        m_ActionTypes.Insert("ia_interact");
        m_ActionTypes.Insert("ia_continuous_interact");
        m_ActionTypes.Insert("ia_single");
        m_ActionTypes.Insert("ia_continuous");

        CreateBlockingIcons();
    }

    protected void CreateBlockingIcons()
    {
        foreach (string action : m_ActionTypes)
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
            m_BlockingIcons.Insert(blockedIconWidget);
        }
    }

    override protected void SetActionWidget(ActionBase action, string descText, string actionWidget, string descWidget)
    {
        Widget widget = m_Root.FindAnyWidget(actionWidget);

        if (action && (!action.HasTarget() || (m_Player && m_Player.GetCommand_Vehicle())))
        {
	        TextWidget actionName = TextWidget.Cast(widget.FindAnyWidget(descWidget));
	        Widget actionIcon = widget.FindAnyWidget(actionWidget + "_btn_icon");
			string blockedIconId = action.GetBlockedIcon(m_Player, null, ItemBase.Cast(m_EntityInHands));
			Widget blockedIconWidget = actionIcon.GetParent().FindAnyWidget(actionWidget + "_" + blockedIconId);

            bool isBlocked = action.IsBlocked(m_Player, null, ItemBase.Cast(m_EntityInHands));

            if (!isBlocked && action.GetInput().GetInputType() == ActionInputType.AIT_CONTINUOUS)
            {
                descText = descText + " " + "#action_target_cursor_hold";
                actionName.SetText(descText);
                actionIcon.Show(true);
                foreach (Widget icon : m_BlockingIcons)
                {
                    icon.Show(false);
                }
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