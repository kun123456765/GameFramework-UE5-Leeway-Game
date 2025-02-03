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

    struct FSetByCaller
    {
        FSetByCaller();
        FNativeGameplayTag Healing;
        FNativeGameplayTag Replenish;
        FNativeGameplayTag Damage;
    } SetByCaller;

private:
    FLWGameplayTags() {}
    static FLWGameplayTags Singleton;
};
