////--------------------
//// kun 2025.02.02
////--------------------
//
//#include "GERequirement_TimeSeniceLastDamage.h"
//#include "Leeway/GameplayAbilities/AttributeSets/CombatAttributeSet.h"
//#include "Leeway/GameplayAbilities/Effects/GameplayEffect_HealthGeneration.h"
//
//bool UGERequirement_TimeSeniceLastDamage::CanApplyGameplayEffect_Implementation(const UGameplayEffect* GameplayEffect, const FGameplayEffectSpec& Spec, UAbilitySystemComponent* ASC) const
//{
//    //ASC->FindActiveGameplayEffectHandle
//    if (const auto* GE = Cast<UGameplayEffect_HealthGeneration>(GameplayEffect))
//    {
//        //ASC->GetActiveGameplayEffect();
//        auto* CombatSet = Cast<UCombatAttributeSet>(ASC->GetAttributeSet(UCombatAttributeSet::StaticClass()));
//        float Now = GetWorld()->GetTime().GetWorldTimeSeconds();
//        float Last = CombatSet->LastDamageWorldTime;
//        float Interval = GE->DamageIntervalWorldTime;
//
//        if (Now - Last > Interval)
//        {
//            float HealthRatio = CombatSet->GetHealth() / CombatSet->GetMaxHealth();
//            if (HealthRatio <= GE->InhibitionRatio)
//            {
//                return true;
//            }
//        }
//    }
//    
//    return false;
//}
