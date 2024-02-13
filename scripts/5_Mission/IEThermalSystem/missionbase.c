#ifdef rag_liquid_framework
class FreezableWater : LiquidDetailsBase
{
    override string GetName(ItemBase item)
    {
        if (item)
        {
            int temperature = item.GetTemperature();
            if (temperature < 0)
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
            if (temperature < 0)
            {
                return IE_COLOR_ICE;
            }
        }
        return Colors.COLOR_LIQUID;
    }
}

modded class MissionBase
{
    void MissionBase()
    {
        auto registry = GetLiquidFrameworkRegistry();
        registry.RegisterLiquid(LIQUID_WATER, new FreezableWater(), true);
    }
}
#endif