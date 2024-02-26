class IE_EnvironmentConfigV1
{
    float player_comfort_temp_low = 20;
    float player_comfort_temp_hi = 35;
    float item_temp_effect_on_player = 60;
}

class IE_ThermalSystemConfigV1 {
    int version = 1;
    bool clothing_has_temperature = true;
    bool edibles_have_temperature = true;
    bool can_consume_frozen_edibles = false;
    bool water_freezes = true;
    bool water_well_temperature = 5.0;
    ref IE_EnvironmentConfigV1 environment;
}

class IE_ThermalSystemVersion
{
  int version;
}

class IE_EnvironmentConfig
{
  float player_comfort_temp_low = 20;
  float player_comfort_temp_hi = 35;
  float item_temp_effect_on_player = 60;
  float thermal_conductivity_rate = 1;
  bool items_affect_player_temperature = 1;
  bool inventory_items_warmup = 1;
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

class IE_ThermalSystemConfigV2
{
  int version = 3;
  bool clothing_has_temperature = true;
  bool edibles_have_temperature = true;
  bool can_consume_frozen_edibles = false;
  bool water_freezes = true;
  float water_well_temperature = 5.0;
  bool frozen_edibles_decay = 0;
  ref IE_EnvironmentConfig environment = new IE_EnvironmentConfig;
  ref array<ref IE_SpecificHeatCapacity> heat_capacities = IE_DefaultHeatCapacities();
  ref array<string> frozen_edibles = IE_DefaultFrozenConsumables();
}

class IE_ThermalSystemConfigV3
{
  int version = 3;
  bool clothing_has_temperature = true;
  bool edibles_have_temperature = true;
  bool can_consume_frozen_edibles = false;
  bool water_freezes = true;
  float water_well_temperature = 5.0;
  bool frozen_edibles_decay = 0;
  float skinning_item_temperature = 30;
  float fishing_item_temperature = 5;
  ref IE_EnvironmentConfig environment = new IE_EnvironmentConfig;
  ref array<ref IE_SpecificHeatCapacity> heat_capacities = IE_DefaultHeatCapacities();
  ref array<string> frozen_edibles = IE_DefaultFrozenConsumables();
}

class IE_ThermalSystemConfig
{
  int version = 4;
  bool clothing_has_temperature = true;
  bool edibles_have_temperature = true;
  bool can_consume_frozen_edibles = false;
  bool water_freezes = true;
  float water_well_temperature = 5.0;
  bool frozen_edibles_decay = 0;
  float skinning_item_temperature = 30;
  float fishing_item_temperature = 5;
  ref IE_EnvironmentConfig environment = new IE_EnvironmentConfig;
  ref array<ref IE_SpecificHeatCapacity> heat_capacities = IE_DefaultHeatCapacities();
  ref array<string> frozen_edibles = IE_DefaultFrozenConsumables();
  ref array<string> forced_affects_comfort = IE_DefaultForcedHeatTransfer();
}

array<string> IE_DefaultForcedHeatTransfer()
{
	array<string> items = new array<string>;
	items.Insert("Heatpack");
	return items;
}

array<string> IE_DefaultFrozenConsumables()
{
  array<string> items = new array<string>;
  items.Insert("BoxCerealCrunchin");
  items.Insert("PowderedMilk");
  items.Insert("Rice");
  items.Insert("Zagorky_ColorBase");
  items.Insert("Snack_ColorBase");
  return items;
}

array<ref IE_SpecificHeatCapacity> IE_DefaultHeatCapacities()
{
  array<ref IE_SpecificHeatCapacity> heat_capacities = new array<ref IE_SpecificHeatCapacity>;
  heat_capacities.Insert(new IE_SpecificHeatCapacity("Clothing", 1.5, 0.7));
  heat_capacities.Insert(new IE_SpecificHeatCapacity("Edible_Base", 2.98, 0.599));
  heat_capacities.Insert(new IE_SpecificHeatCapacity("Heatpack", 5, 0.6));
  heat_capacities.Insert(new IE_SpecificHeatCapacity("Object", 1.012, 0.02535));
  return heat_capacities;
}

class IE_ThermalSystemConfigLoader
{

  static private const string DIR_PATH = "$profile:IE";
  static private const string CONFIG_PATH = DIR_PATH + "\\ThermalSystem.json";
  static private const string CONFIG_PATH_V1 = DIR_PATH + "\\ThermalSystem.json.v1back";
  static private const string CONFIG_PATH_V2 = DIR_PATH + "\\ThermalSystem.json.v2back";
  static private const string CONFIG_PATH_V3 = DIR_PATH + "\\ThermalSystem.json.v3back";

  ref IE_ThermalSystemConfig config = new IE_ThermalSystemConfig;

  void Load()
  {
    if (!FileExist(DIR_PATH))
    {
      MakeDirectory(DIR_PATH);
    }

    if (FileExist(CONFIG_PATH))
    { // If config exist load File
      IE_ThermalSystemVersion v;
      JsonFileLoader<IE_ThermalSystemVersion>.JsonLoadFile(CONFIG_PATH, v);
      if (v.version == 4)
      {
        JsonFileLoader<IE_ThermalSystemConfig>.JsonLoadFile(CONFIG_PATH, config);
      }
      else if (v.version == 1)
      {
        IE_ThermalSystemConfigV1 v1;
        JsonFileLoader<IE_ThermalSystemConfigV1>.JsonLoadFile(CONFIG_PATH, v1);
        config.clothing_has_temperature = v1.clothing_has_temperature;
        config.edibles_have_temperature = v1.edibles_have_temperature;
        config.can_consume_frozen_edibles = v1.can_consume_frozen_edibles;
        config.water_freezes = v1.water_freezes;
        config.environment.player_comfort_temp_low = v1.environment.player_comfort_temp_low;
        config.environment.player_comfort_temp_hi = v1.environment.player_comfort_temp_hi;
        config.environment.item_temp_effect_on_player = v1.environment.item_temp_effect_on_player;
        JsonFileLoader<IE_ThermalSystemConfigV1>.JsonSaveFile(CONFIG_PATH_V1, v1);
        Save();
      }
      else if (v.version == 2)
      {
        IE_ThermalSystemConfigV2 v2;
        JsonFileLoader<IE_ThermalSystemConfigV2>.JsonLoadFile(CONFIG_PATH, v2);
        config.clothing_has_temperature = v2.clothing_has_temperature;
        config.edibles_have_temperature = v2.edibles_have_temperature;
        config.can_consume_frozen_edibles = v2.can_consume_frozen_edibles;
        config.water_freezes = v2.water_freezes;
        config.environment = v2.environment;
        config.frozen_edibles = v2.frozen_edibles;
        config.heat_capacities = v2.heat_capacities;
        JsonFileLoader<IE_ThermalSystemConfigV2>.JsonSaveFile(CONFIG_PATH_V2, v2);
        Save();
      }
	  else if (v.version == 3)
	  {
        IE_ThermalSystemConfigV3 v3;
        JsonFileLoader<IE_ThermalSystemConfigV3>.JsonLoadFile(CONFIG_PATH, v3);
        config.clothing_has_temperature = v3.clothing_has_temperature;
        config.edibles_have_temperature = v3.edibles_have_temperature;
        config.can_consume_frozen_edibles = v3.can_consume_frozen_edibles;
	    config.water_well_temperature = v3.water_well_temperature;
        config.water_freezes = v3.water_freezes;
		config.skinning_item_temperature = v3.skinning_item_temperature;
		config.fishing_item_temperature = v3.fishing_item_temperature;
        config.environment = v3.environment;
        config.frozen_edibles = v3.frozen_edibles;
        config.heat_capacities = v3.heat_capacities;
        JsonFileLoader<IE_ThermalSystemConfigV3>.JsonSaveFile(CONFIG_PATH_V3, v3);
		Save();
	  }
      else
      {
        Print("[Thermal System] ERROR! Non recognised version.");
      }
    }
    else
    {
      Save();
    }
  }

  void Save()
  {
    if (GetGame().IsServer())
    {
      JsonFileLoader<ref IE_ThermalSystemConfig>.JsonSaveFile(CONFIG_PATH, config);
    }
  }

  void RequestConfiguration()
  {
    GetRPCManager().SendRPC("IE_ThermalSystem", "RequestConfigurationRPC", null, true);
  }

  void RequestConfigurationRPC(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
  {
    Param1<IE_ThermalSystemConfig> data;
    if (ctx.Read(data))
    {
      config = data.param1;
    }
    else if (GetGame().IsServer())
    {
      GetRPCManager().SendRPC("IE_ThermalSystem", "RequestConfigurationRPC", new Param1<IE_ThermalSystemConfig>(config), true, sender, target);
    }
  }
}

static ref IE_ThermalSystemConfigLoader g_IE_ThermalSystemConfigLoader;

static IE_ThermalSystemConfigLoader GetThermalSystemConfigLoader()
{
  if (!g_IE_ThermalSystemConfigLoader)
  {
    g_IE_ThermalSystemConfigLoader = new IE_ThermalSystemConfigLoader();
    if (GetGame().IsServer())
    {
      g_IE_ThermalSystemConfigLoader.Load();
    }
  }
  return g_IE_ThermalSystemConfigLoader;
}

static IE_ThermalSystemConfig GetThermalSystemConfig()
{
  return GetThermalSystemConfigLoader().config;
}