//--------------------
// kun 2025.01.25
//--------------------

#include "BaseEffectExecution.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffectExecutionCalculation.h"

void UBaseEffectExecution::GetValidScopedModifierAttributeCaptureDefinitions(OUT TArray<FGameplayEffectAttributeCaptureDefinition>& OutScopableModifiers) const
{
    Super::GetValidScopedModifierAttributeCaptureDefinitions(OutScopableModifiers);
}

const FGameplayTagContainer& UBaseEffectExecution::GetValidTransientAggregatorIdentifiers() const
{
    return Super::GetValidTransientAggregatorIdentifiers();
}

bool UBaseEffectExecution::DoesRequirePassedInTags() const
{
    return Super::DoesRequirePassedInTags();
}

void UBaseEffectExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
}
