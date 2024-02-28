modded class ColorManager
{
    override int GetItemColor(ItemBase item)
    {
        int color = -1;
        ItemBase dragged_item = ItemBase.Cast(ItemManager.GetInstance().GetDraggedItem());
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());

        if (dragged_item)
            return 0;

        if (item)
        {
            // if item icon is main icon (view, viewgrid )
            if (item.GetHierarchyParent() && item.GetHierarchyParent() != player)
            {
                color = -1;
            }

            if (item.IsTemperatureVisible())
            {
                float temperature = item.GetTemperature();
                color = IEGetTemperatureColor(temperature);
            }
        }
        return color;
    }
}