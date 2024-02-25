class IE_EnvironmentConfig
{
    float player_comfort_temp_low = 20;
    float player_comfort_temp_hi = 35;
    float item_temp_effect_on_player = 60;
    float thermal_conductivity_coefficient = 1;
}

class IE_SpecificHeatCapacity
{
  string item;
  float heat_capacity;
  float thermal_conductivity;

  void IE_SpecificHeatCapacity(string itm, float capacity, float conductivity)
  {
    item = itm;
    heat_capacity = capacity;
    thermal_conductivity = conductivity;
  }
}

class IE_ThermalSystemConfig {
    int version = 1;
    bool clothing_has_temperature = true;
    bool edibles_have_temperature = true;
    bool can_consume_frozen_edibles = false;
    bool water_freezes = true;
    bool water_well_temperature = 5.0;
    ref IE_EnvironmentConfig environment = new IE_EnvironmentConfig;
    ref array<ref IE_SpecificHeatCapacity> heat_capacities = IE_DefaultHeatCapacities();
	
}

array<ref IE_SpecificHeatCapacity> IE_DefaultHeatCapacities()
{
  array<ref IE_SpecificHeatCapacity> heat_capacities = new array<ref IE_SpecificHeatCapacity>;
  heat_capacities.Insert(new IE_SpecificHeatCapacity("Clothing", 1.5, 0.03));
  heat_capacities.Insert(new IE_SpecificHeatCapacity("Edible_Base", 2.98, 0.599));
  heat_capacities.Insert(new IE_SpecificHeatCapacity("Object", 1.012, 0.02535));
  return heat_capacities;
}

class IE_ThermalSystemConfigLoader {
  
  static private const string DIR_PATH = "$profile:IE";
  static private const string CONFIG_PATH = DIR_PATH + "\\ThermalSystem.json";
  
  ref IE_ThermalSystemConfig config = new IE_ThermalSystemConfig;
  
  void Load() {
    if (!FileExist(DIR_PATH)){
        MakeDirectory(DIR_PATH);
    }

    if (FileExist(CONFIG_PATH)){ //If config exist load File
        JsonFileLoader<ref IE_ThermalSystemConfig>.JsonLoadFile(CONFIG_PATH, config);
    } else {
		Save();
	}
  }
  
  void Save() {
	if (GetGame().IsServer()) {
         JsonFileLoader<ref IE_ThermalSystemConfig>.JsonSaveFile(CONFIG_PATH, config);
	}
  }

  void RequestConfiguration() {
	GetRPCManager().SendRPC("IE_ThermalSystem", "RequestConfigurationRPC", null, true);
  }

  void RequestConfigurationRPC( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target ) {
    Param1<IE_ThermalSystemConfig> data;
    if (ctx.Read(data)) {
      config = data.param1;
    } else if (GetGame().IsServer()) {
        GetRPCManager().SendRPC("IE_ThermalSystem", "RequestConfigurationRPC", new Param1<IE_ThermalSystemConfig>(config), true, sender, target);
    }
  }
}

static ref IE_ThermalSystemConfigLoader g_IE_ThermalSystemConfigLoader;

static IE_ThermalSystemConfigLoader GetThermalSystemConfigLoader() {
    if (!g_IE_ThermalSystemConfigLoader) {
      g_IE_ThermalSystemConfigLoader = new IE_ThermalSystemConfigLoader();
	  if(GetGame().IsServer()) {
      	g_IE_ThermalSystemConfigLoader.Load();
	  }
    }
    return g_IE_ThermalSystemConfigLoader;
}

static IE_ThermalSystemConfig GetThermalSystemConfig() {
    return GetThermalSystemConfigLoader().config;
}