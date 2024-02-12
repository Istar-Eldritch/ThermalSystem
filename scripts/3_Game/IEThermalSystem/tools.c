int IEGetTemperatureColor( int temperature )
{
	int alpha = 128;
	int red = 153;
	int green = 153;
	int blue = 153;
    if (temperature < 0)
    {
        return 0xffACC8E5;
    }
	else if ( temperature < 20 )
	{
		temperature = temperature - 20;
		temperature = Math.Clamp( temperature, -50, 50);
		temperature = Math.AbsInt(temperature);

		red = Math.Clamp ( red - ((red/50 )*temperature), 0, 255 );
		green = Math.Clamp ( green - ((green/50 )*temperature), 0, 255 );
		blue = Math.Clamp ( blue+((blue/50)*temperature), 0, 255 );
	}
	else if ( temperature > 20 )
	{
		temperature = Math.Clamp( temperature, -100, 100);
		blue = Math.Clamp ( blue - ((blue/100 )*temperature), 0, 255 );
		green = Math.Clamp ( green - ((green/100 )*temperature), 0, 255 );
		red = Math.Clamp ( red+((red/100)*temperature), 0, 255 );
	}

	int color = ARGB( alpha, red, green, blue );
	return color;
}