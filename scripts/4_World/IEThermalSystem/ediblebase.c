modded class Edible_Base: ItemBase {

	override bool CanHaveTemperature() {
		return true;
	}

    bool CanBeConsumedFrozen() {
        return false;
    }
}