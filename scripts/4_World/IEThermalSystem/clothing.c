modded class Clothing
{
    override bool CanHaveTemperature()
    {
        return GetThermalSystemConfig().clothing_has_temperature;
    }
}