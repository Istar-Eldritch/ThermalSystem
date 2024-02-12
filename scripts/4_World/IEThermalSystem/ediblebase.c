modded class Edible_Base: ItemBase {

    override bool IsTemperatureVisible() {
        return true;
    }
	
	override bool CanHaveTemperature() {
		return true;
	}
}