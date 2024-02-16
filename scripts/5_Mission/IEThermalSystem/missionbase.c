#ifdef rag_liquid_framework
class FreezableWater : LiquidDetailsBase
{
    override string GetName(ItemBase item)
    {
        if (item)
        {
            int temperature = item.GetTemperature();
            if (temperature < 0 && GetThermalSystemConfig().water_freezes)
            {
                return "ICE";
            }
        }
        return "#inv_inspect_water";
    }

    override int GetColor(ItemBase item)
    {
        if (item)
        {
            int temperature = item.GetTemperature();
            if (temperature < 0 && GetThermalSystemConfig().water_freezes)
            {
                return IE_COLOR_ICE;
            }
        }
        return Colors.COLOR_LIQUID;
    }
}
#endif


modded class MissionBase
{
    void MissionBase()
    {
        #ifdef rag_liquid_framework
            auto registry = GetLiquidFrameworkRegistry();
            registry.RegisterLiquid(LIQUID_WATER, new FreezableWater(), true);
        #endif
        IE_ThermalSystemConfigLoader loader = GetThermalSystemConfigLoader();
        GetRPCManager().AddRPC("IE_ThermalSystem", "RequestConfigurationRPC", loader, SingleplayerExecutionType.Both);
        if (GetGame().IsClient()) {
            loader.RequestConfiguration();
        }
    }
}