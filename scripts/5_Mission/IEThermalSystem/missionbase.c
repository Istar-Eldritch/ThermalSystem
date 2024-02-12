// class FreezableWater: LiquidDetailsBase
// {
//     string GetName(ItemBase item) {
//         int temperature = item && item.GetTemperature();
// 		if (temperature < 0) {
//             return "ICE";
// 		} else {
//             return "#inv_inspect_water";
//         }
//     }
//     int GetColor(ItemBase item) {
//         int temperature = item && item.GetTemperature();
// 		if (temperature < 0) {
//             return COLOR_GRAY;
// 		} else {
//             return COLOR_LIQUID;
//         }
//     }
// }

// modded class MissionBase {
//   void MissionBase() {
//     #ifdef rag_liquid_framework
//         auto registry = GetLiquidFrameworkRegistry();
//         registry.RegisterLiquid(LIQUID_WATER, new FreezableWater(), true);
//     #endif
//   }
// }
