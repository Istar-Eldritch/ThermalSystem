class CfgPatches
{
	class IE_ThermalSystem_Scripts
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] =
			{
				"DZ_Data",
				"DZ_Scripts",
				"JM_CF_Scripts",
				"IE_ThermalSystem_Assets"};
	};
};

class CfgMods
{
	class IEThermalSystem
	{
		type = "mod";
		author = "Istar Eldritch";

		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"IE/ThermalSystem/scripts/3_Game"};
			};

			class worldScriptModule
			{
				value = "";
				files[] = {"IE/ThermalSystem/scripts/4_World"};
			};

			class missionScriptModule
			{
				value = "";
				files[] = {"IE/ThermalSystem/scripts/5_Mission"};
			};
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class Bottle_Base;
	class Edible_Base : Inventory_Base
	{
		scope = 2;
		varTemperatureMin = -273;
		varTemperatureMax = 100;
		inventorySlot[] =
			{
				"DirectCookingA",
				"DirectCookingB",
				"DirectCookingC"};
	};

	class Clothing : Inventory_Base
	{
		scope = 2;
		varTemperatureMin = -273;
		varTemperatureMax = 200;
	}

	class WaterBottle : Bottle_Base
	{
		scope = 2;
		varTemperatureMax = 100;
	};
	class Canteen : Bottle_Base
	{
		scope = 2;
		varTemperatureMax = 100;
	};
	class WaterPouch_ColorBase : Bottle_Base
	{
		scope = 2;
		varTemperatureMax = 100;
	};

	class FoodCan_100g_ColorBase: Edible_Base
	{
		scope = 2;
		varTemperatureMax = 100;
	};


	class FoodCan_250g_ColorBase: Edible_Base
	{
		scope = 2;
		varTemperatureMax = 100;
	};
};