modded class ItemActionsWidget
{
    ImageWidget m_IEActionFrozen;

    override protected void OnWidgetScriptInit(Widget w)
	{
        super.OnWidgetScriptInit(w);

        array<string> actionTypes = new array<string>;
		actionTypes.Insert("ia_interact");
		actionTypes.Insert("ia_continuous_interact");
		actionTypes.Insert("ia_single");
		actionTypes.Insert("ia_continuous");
		
		foreach(string action: actionTypes)
		{
			Widget existingIcon = m_Root.FindAnyWidget(action + "_btn_icon");
			m_IEActionFrozen = ImageWidget.Cast(GetGame().GetWorkspace().CreateWidgets("IE/ThermalSystem/assets/layouts/ie_thermalsystem_snowflake_icon.layout", existingIcon.GetParent()));
			m_IEActionFrozen.Show(false);
		}

	}

	override protected void BuildCursor()
	{
		int health 				= -1;
		int quantityType 		= 0;
		int quantityMin			= -1;
		int quantityMax 		= -1;
		float quantityCurrent 	= -1.0;

		m_IEActionFrozen.Show(false);
		// item health
		health = GetItemHealth();
		SetItemHealth(health, "ia_item", "ia_item_health_mark", m_HealthEnabled);
		
		// quantity
		//! weapon specific
		if (m_EntityInHands && m_EntityInHands.IsWeapon())
		{
			SetWeaponQuantity(0, 0, "ia_item", "ia_item_quantity_pb", "ia_item_quantity_text", m_QuantityEnabled);
			SetWeaponModeAndZeroing("ia_item_subdesc", "ia_item_subdesc_up", "ia_item_subdesc_down", true);
		}
		//! transmitter/PAS specific
		else if (m_EntityInHands && m_EntityInHands.IsTransmitter())
		{
			SetRadioFrequency(GetRadioFrequency(), "ia_item_subdesc", "ia_item_subdesc_up", "ia_item_subdesc_down", m_QuantityEnabled);
			GetItemQuantity(quantityType, quantityCurrent, quantityMin, quantityMax);
			SetItemQuantity(quantityType, quantityCurrent, quantityMin, quantityMax, "ia_item", "ia_item_quantity_pb", "ia_item_quantity_text", true);
		}
		else
		{
			GetItemQuantity(quantityType, quantityCurrent, quantityMin, quantityMax);
			SetItemQuantity(quantityType, quantityCurrent, quantityMin, quantityMax, "ia_item", "ia_item_quantity_pb", "ia_item_quantity_text", m_QuantityEnabled);
			SetWeaponModeAndZeroing("ia_item_subdesc", "", "", false);
		}
	
		SetItemDesc(m_EntityInHands, GetItemDesc(m_EntityInHands), "ia_item", "ia_item_desc");
		SetInteractActionIcon("ia_interact", "ia_interact_icon_frame", "ia_interact_btn_inner_icon", "ia_interact_btn_text");
		SetActionWidget(m_Interact, GetActionDesc(m_Interact), "ia_interact", "ia_interact_action_name", "ia_interact_btn_icon");

		SetInteractActionIcon("ia_continuous_interact", "ia_continuous_interact_icon_frame", "ia_continuous_interact_btn_inner_icon", "ia_continuous_interact_btn_text");
		SetActionWidget(m_ContinuousInteract, GetActionDesc(m_ContinuousInteract), "ia_continuous_interact", "ia_continuous_interact_action_name", "ia_continuous_interact_btn_icon");

		SetActionWidget(m_Single, GetActionDesc(m_Single), "ia_single", "ia_single_action_name", "ia_single_btn_icon");
		SetActionWidget(m_Continuous, GetActionDesc(m_Continuous), "ia_continuous", "ia_continuous_action_name", "ia_continuous_btn_icon");
		SetMultipleInteractAction("ia_interact_mlt_wrapper");
		SetMultipleContinuousInteractAction("ia_continuous_interact_mlt_wrapper");
		SetMultipleItemAction("ia_single_mlt_wrapper");
		SetMultipleContinuousItemAction("ia_continuous_mlt_wrapper");
	}

	protected void SetActionWidget(ActionBase action, string descText, string actionWidget, string descWidget, string actionIconWidget)
	{
		Widget widget = m_Root.FindAnyWidget(actionWidget);
	
		if (action && (!action.HasTarget() || (m_Player && m_Player.GetCommand_Vehicle())))
		{
			TextWidget actionName = TextWidget.Cast(widget.FindAnyWidget(descWidget));
            Widget actionIcon = widget.FindAnyWidget(actionIconWidget);
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
                    actionIcon.Show(false);

                    actionName.SetText(action.GetBlockedText(m_Player, null, ItemBase.Cast(m_EntityInHands)));
					string blockedIconId = action.GetBlockedIcon(m_Player, null, ItemBase.Cast(m_EntityInHands));
                    Widget blockedIconWidget = actionIcon.GetParent().FindAnyWidget(blockedIconId);
					if (blockedIconWidget)
					{
	                    float x;
	                   	float y;
						actionIcon.GetScreenPos(x, y);
						blockedIconWidget.SetScreenPos(x, y);
						float width;
						float height;
						actionIcon.GetScreenSize(width, height);
						blockedIconWidget.SetScreenSize(width, height);
						blockedIconWidget.Show(true);
					}
                }
                else
                {
                    actionIcon.Show(true);
                    actionName.SetText(descText);
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