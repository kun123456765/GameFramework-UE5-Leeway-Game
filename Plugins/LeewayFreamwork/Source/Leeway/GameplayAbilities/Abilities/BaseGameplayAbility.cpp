//--------------------
// kun 2025.01.23
//--------------------

#include "BaseGameplayAbility.h"

bool UBaseGameplayAbility::DoesAbilitySatisfyTagRequirements(const UAbilitySystemComponent& AbilitySystemComponent, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
    //UE_CLOG_EX(NSLeeway::MontageLogLevel, LogAbilitySystemComponent, Log, TEXT(""));
    return Super::DoesAbilitySatisfyTagRequirements(AbilitySystemComponent, SourceTags, TargetTags, OptionalRelevantTags);
}
