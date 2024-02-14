modded class IngameHud
{
    ImageWidget m_IEActionFrozen;

    override void Init(Widget hud_panel_widget)
    {
        super.Init(hud_panel_widget);
        m_IEActionFrozen = ImageWidget.Cast(GetGame().GetWorkspace().CreateWidgets("IE/ThermalSystem/assets/layouts/ie_thermalsystem_snowflake_icon.layout", m_ActionWidget));
        m_IEActionFrozen.Show(false);
    }
}