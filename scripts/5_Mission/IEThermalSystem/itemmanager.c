modded class ItemManager
{
    override void SetTemperature(EntityAI item, Widget item_w)
	{
		if ( item_w )
		{
			if ( true/*show_temperature */ )
			{
				if ( item && item.IsInherited( ItemBase ) )
				{
					int color = ColorManager.GetInstance().GetItemColor( ItemBase.Cast( item ) ); // !!!!!
					if ( color )
					{
						string name = item_w.GetName();
						name.Replace("Render", "Temperature");
						Widget temperature_widget = item_w.GetParent().FindAnyWidget( name );
						if ( color != -1 )
						{
							temperature_widget.Show( true );
							temperature_widget.SetColor( color );
						}
						else
						{
							temperature_widget.Show( false );
						}

						temperature_widget.SetAlpha( 0.3 );
					}
				}
			}
		}
	}

	override void SetIconTemperature(EntityAI item, Widget item_w)
	{
		if ( item_w )
		{
			if ( item && item.IsInherited( ItemBase ) )
			{
				int color = ColorManager.GetInstance().GetItemColor( ItemBase.Cast( item ) );

				if ( color )
				{
					Widget color_widget = item_w.FindAnyWidget( "Color" );
					if( color_widget && color != -1 )
					{
						color_widget.SetColor( color );
					}
					else if (color_widget)
					{
						color_widget.SetColor( ColorManager.BASE_COLOR );
					}
				}
			}
		}
	}
}