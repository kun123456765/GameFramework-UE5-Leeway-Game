//--------------------
// kun 2025.01.25
//--------------------

#include "CombatEffectExecution.h"

void UCombatEffectExecution::GetValidScopedModifierAttributeCaptureDefinitions(OUT TArray<FGameplayEffectAttributeCaptureDefinition>& OutScopableModifiers) const
{
    Super::GetValidScopedModifierAttributeCaptureDefinitions(OutScopableModifiers);
}

const FGameplayTagContainer& UCombatEffectExecution::GetValidTransientAggregatorIdentifiers() const
{
    return Super::GetValidTransientAggregatorIdentifiers();
}

bool UCombatEffectExecution::DoesRequirePassedInTags() const
{
    return Super::DoesRequirePassedInTags();
}

void UCombatEffectExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
}
