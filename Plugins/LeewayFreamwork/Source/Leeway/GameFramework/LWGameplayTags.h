//--------------------
// kun 2025.02.02
//--------------------

#pragma once

class FLWGameplayTags
{
public:
    static FLWGameplayTags& Get()
    {
        return Singleton;
    }

    struct FGALabel
    {
        FGALabel();
        FNativeGameplayTag IgnoreToDeath;
        FNativeGameplayTag IgnoreToUninitial;
    } GALabel;

    struct FSetByCaller
    {
        FSetByCaller();
        FNativeGameplayTag Healing;
        FNativeGameplayTag Replenish;
        FNativeGameplayTag Damage;
    } SetByCaller;

    struct FGameEvent
    {
        FGameEvent();
        FNativeGameplayTag Death;
        FNativeGameplayTag Revive;
    } GameEvent;

private:
    FLWGameplayTags() {}
    static FLWGameplayTags Singleton;
};
