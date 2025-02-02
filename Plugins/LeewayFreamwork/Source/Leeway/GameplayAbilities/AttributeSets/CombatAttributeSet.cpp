//--------------------
// kun 2025.01.23
//--------------------

#include "CombatAttributeSet.h"
#include "GameplayEffectExtension.h"

void UCombatAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, Health, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, MaxHealth, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, Shield, COND_None, REPNOTIFY_OnChanged);
    DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, MaxShield, COND_None, REPNOTIFY_OnChanged);
}

bool UCombatAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
    if (!Super::PreGameplayEffectExecute(Data))
    {
        return false;
    }

    BeforeChangeValues.MaxHealth = GetMaxHealth();

    return true;
}

void UCombatAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);

    const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
    AActor* Instigator = EffectContext.GetOriginalInstigator();
    AActor* Causer = EffectContext.GetEffectCauser();

    //note by kun 2025.02.02
    // 只有伤害才有事件,其他都只是值改变;
    // 也许这样不好，可以改成根据血量变化去包装事件，做AttributeSet外面会丢失变化原因，要做只能里面做。

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
    }
    else if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
    {
        SetMaxHealth(FMath::Clamp(GetHealth(), 1, GetMaxHealth()));

        //note by kun 2025.02.01
        // 给玩家的彩蛋,换装回血大法!
        float OverHealing = GetMaxHealth() - BeforeChangeValues.MaxHealth;
        if (OverHealing > 0)
        {
            SetHealth(FMath::Clamp(GetHealth() + OverHealing, 0, GetMaxHealth()));
        }
    }
    else if (Data.EvaluatedData.Attribute == GetShieldAttribute())
    {
        SetShield(FMath::Clamp(GetShield(), 0, GetMaxShield()));
    }
    else if (Data.EvaluatedData.Attribute == GetMaxShieldAttribute())
    {
        SetMaxShield(FMath::Clamp(GetMaxShield(), 0, GetMaxShield()));
        SetShield(FMath::Clamp(GetShield(), 0, GetMaxShield()));
    }
    else if (Data.EvaluatedData.Attribute == GetHealingAttribute())
    {
        const float HealthValue = GetHealth();
        const float MaxHealthValue = GetMaxHealth();
        const float RawHealing = GetHealing();
        float FinalHealing = RawHealing;
        if (HealthValue + RawHealing > MaxHealthValue)
        {
            FinalHealing = FMath::Max(0, MaxHealthValue - HealthValue);
        }
        if (FinalHealing < RawHealing)
        {
            SetHealth(MaxHealthValue);
        }
        else
        {
            SetHealth(HealthValue + FinalHealing);
        }
        SetHealing(0);
        FHealingInfo HealingInfo;
        HealingInfo.Healing = FinalHealing;
        OnHealing.Broadcast(HealingInfo);
    }
    else if (Data.EvaluatedData.Attribute == GetReplenishAttribute())
    {
        const float ShieldValue = GetShield();
        const float MaxShieldValue = GetMaxShield();
        const float RawReplenish = GetReplenish();
        float FinalReplenish = RawReplenish;
        if (ShieldValue + RawReplenish > MaxShieldValue)
        {
            FinalReplenish = FMath::Max(0, MaxShieldValue - ShieldValue);
        }
        if (FinalReplenish < RawReplenish)
        {
            SetHealth(MaxShieldValue);
        }
        else
        {
            SetHealth(ShieldValue + FinalReplenish);
        }
        SetReplenish(0);
        FHealingInfo HealingInfo;
        HealingInfo.Replenish = FinalReplenish;
        OnHealing.Broadcast(HealingInfo);
    }
    else if (Data.EvaluatedData.Attribute == GetDamageAttribute())
    {
        const float HealthValue = GetHealth();
        const float ShieldValue = GetShield();
        const float HealingValue = GetHealing();
        const float ReplenishValue = GetReplenish();
        const float RawDamage = GetDamage();
        float FinalDamage = RawDamage;

        if (FinalDamage > 0 && ReplenishValue > 0)
        {
            if (FinalDamage >= ReplenishValue)
            {
                FinalDamage -= ReplenishValue;
                SetReplenish(0);
            }
            else
            {
                SetReplenish(ReplenishValue - FinalDamage);
                FinalDamage = 0;
            }
        }

        if (FinalDamage > 0 && HealingValue > 0)
        {
            if (FinalDamage >= HealingValue)
            {
                FinalDamage -= HealingValue;
                SetHealing(0);
            }
            else
            {
                SetHealing(HealingValue - FinalDamage);
                FinalDamage = 0;
            }
        }

        if (FinalDamage > 0)
        {
            FDamageInfo DamageInfo;
            bool bNeedBroadcast_ShieldBroken = false;
            bool bNeedBroadcast_OutOfHealth = false;

            if (FinalDamage > 0 && ShieldValue > 0)
            {
                if (FinalDamage >= ShieldValue)
                {
                    FinalDamage -= ShieldValue;
                    SetShield(0);

                    DamageInfo.ShieldDamage = ShieldValue;

                    if (!bShieldBroken)
                    {
                        bShieldBroken = true;
                        bNeedBroadcast_ShieldBroken = true;
                    }
                }
                else
                {
                    SetShield(FMath::Max(0, ShieldValue - FinalDamage));
                    FinalDamage = 0;

                    DamageInfo.ShieldDamage = FinalDamage;
                }
            }

            if (FinalDamage > 0 && HealthValue > 0)
            {
                if (FinalDamage >= HealthValue)
                {
                    FinalDamage -= HealthValue;
                    SetHealth(0);

                    DamageInfo.HealthDamage = HealthValue;

                    if (!bOutOfHealth)
                    {
                        bOutOfHealth = true;
                        bNeedBroadcast_OutOfHealth = true;
                    }
                }
                else
                {
                    SetHealth(FMath::Max(0, HealthValue - FinalDamage));
                    FinalDamage = 0;

                    DamageInfo.HealthDamage = FinalDamage;
                }
            }

            SetDamage(0);
            LastDamageWorldTime = GetWorld()->GetTime().GetWorldTimeSeconds();
            OnDamge.Broadcast(DamageInfo);

            if (bNeedBroadcast_ShieldBroken || bNeedBroadcast_OutOfHealth)
            {
                FOutOfHealthInfo OutOfHealthInfo;
                OutOfHealthInfo.bShieldBroken = bNeedBroadcast_ShieldBroken;
                OutOfHealthInfo.bOutOfHealth = bNeedBroadcast_OutOfHealth;
                OnOutOfHealth.Broadcast(OutOfHealthInfo);
            }
        }
    }
}

void UCombatAttributeSet::Initialize(float InitMaxHealth)
{
    SetHealth(InitMaxHealth);
    SetMaxHealth(InitMaxHealth);
    SetShield(0);
    SetMaxShield(0);
    SetDamage(0);
    SetHealing(0);
    SetReplenish(0);

    bOutOfHealth = false;
    bShieldBroken = false;
}

void UCombatAttributeSet::OnRep_Health(const FGameplayAttributeData& PrevValue)
{
}

void UCombatAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& PrevValue)
{
}

void UCombatAttributeSet::OnRep_Shield(const FGameplayAttributeData& PrevValue)
{
}

void UCombatAttributeSet::OnRep_MaxShield(const FGameplayAttributeData& PrevValue)
{
}

void UCombatAttributeSet::OnRep_Damage(const FGameplayAttributeData& PrevValue)
{
}

void UCombatAttributeSet::OnRep_Healing(const FGameplayAttributeData& PrevValue)
{
}

void UCombatAttributeSet::OnRep_Replenish(const FGameplayAttributeData& PrevValue)
{
}
