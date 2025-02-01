//--------------------
// kun 2025.01.23
//--------------------

#include "GameplayAbility_Attack.h"

void UGameplayAbility_Melee::OnTakeDamage(const FGameplayTag& TriggerTag, const FGameplayAbilityTargetDataHandle& TargetData)
{
    auto* ASC = GetAbilitySystemComponentFromActorInfo_Checked();
    FGameplayEventData Payload;
    Payload.EventTag = TriggerTag;
    Payload.TargetData = TargetData;
    FScopedPredictionWindow NewScopedWindow(ASC, true);
    ASC->HandleGameplayEvent(TriggerTag, &Payload);
}
