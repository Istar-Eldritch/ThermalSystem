modded class ActionSkinning
{
    override ItemBase CreateOrgan(PlayerBase player, vector body_pos, string item_to_spawn, string cfg_skinning_organ_class, ItemBase tool)
    {
        ItemBase item = super.CreateOrgan(player, body_pos, item_to_spawn, cfg_skinning_organ_class, tool);
        auto config = GetThermalSystemConfig();
        item.SetTemperature(config.skinning_item_temperature);
        return item;
    }
}