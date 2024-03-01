modded class PlayerBase
{

    void IEAddDamage(string type, float damage, bool playSound = false)
    {
        AddHealth("", type, damage * -1);
        if (damage >= 9 && playSound) {
            SendSoundEvent(EPlayerSoundEventID.TAKING_DMG_HEAVY);
        } else {
            SendSoundEvent(EPlayerSoundEventID.TAKING_DMG_LIGHT);
        }

    }
}