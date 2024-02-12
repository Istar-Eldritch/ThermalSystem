class CfgPatches
{
  class IE_ThermalSystem_Scripts
  {
    units[]={};
    weapons[]={};
    requiredVersion=0.1;
    requiredAddons[]=
    {
      "DZ_Data"
    };
  };
};

class CfgMods {
	class IEThermalSystem {
		type = "mod";
    author = "Istar Eldritch";

		class defs {
			class gameScriptModule {
				value = "";
				files[] = {"IE/ThermalSystem/scripts/3_Game"};
			};

			class worldScriptModule {
				value = "";
				files[] = {"IE/ThermalSystem/scripts/4_World"};
			};

			class missionScriptModule {
				value = "";
				files[] = {"IE/ThermalSystem/scripts/5_Mission"};
			};
		};
	};
};

class CfgVehicles {
  class Inventory_Base;
  class Edible_Base: Inventory_Base
	{
		scope=2;
    varTemperatureMin=-273;
		inventorySlot[]=
		{
			"DirectCookingA",
			"DirectCookingB",
			"DirectCookingC"
		};
  }
}