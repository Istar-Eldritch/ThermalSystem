modded class ItemManager
{
    override void SetTemperature(EntityAI item, Widget item_w)
    {
        if (item_w)
        {
            if (item)
            {
                ItemBase itemBase = ItemBase.Cast(item);
                if (itemBase)
                {
                    string name = item_w.GetName();
                    name.Replace("Render", "Temperature");
                    Widget temperature_widget = item_w.GetParent().FindAnyWidget(name);
                    if (temperature_widget)
                    {
                        if (itemBase.IsTemperatureVisible())
                        {
                            float temperature = itemBase.GetTemperature();
                            int color = IEGetTemperatureColor(temperature); // !!!!!
                            if (color && color != -1)
                            {
                                temperature_widget.Show(true);
                                temperature_widget.SetColor(color);
                            }
                            else
                            {
                                temperature_widget.Show(false);
                            }

                            temperature_widget.SetAlpha(0.3);
                        }
                        else
                        {
                            temperature_widget.Show(false);
                        }
                    }
                }
            }
        }
    }

    override void SetIconTemperature(EntityAI item, Widget item_w)
    {
        if (item_w)
        {
            ItemBase itemBase = ItemBase.Cast(item);
            if (itemBase)
            {
                Widget color_widget = item_w.FindAnyWidget("Color");
                if (color_widget)
                {
                    if (itemBase.IsTemperatureVisible())
                    {
                        float temperature = itemBase.GetTemperature();
                        int color = IEGetTemperatureColor(temperature);

                        if (color && color != -1)
                        {
                            color_widget.SetColor(color);
                        }
                        else
                        {
                            color_widget.SetColor(ColorManager.BASE_COLOR);
                        }
                    }
                    else
                    {
                        color_widget.SetColor(ColorManager.BASE_COLOR);
                    }
                }
            }
        }
    }
}