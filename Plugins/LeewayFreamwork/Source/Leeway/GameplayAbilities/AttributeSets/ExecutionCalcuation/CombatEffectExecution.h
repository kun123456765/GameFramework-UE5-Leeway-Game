//--------------------
// kun 2025.01.25
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BaseEffectExecution.h"
#include "AbilitySystemComponent.h"
#include "CombatEffectExecution.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class UCombatEffectExecution : public UBaseEffectExecution
{
	GENERATED_BODY()

public:
	virtual void GetValidScopedModifierAttributeCaptureDefinitions(OUT TArray<FGameplayEffectAttributeCaptureDefinition>& OutScopableModifiers) const override;
	virtual const FGameplayTagContainer& GetValidTransientAggregatorIdentifiers() const override;
	virtual bool DoesRequirePassedInTags() const override;
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
