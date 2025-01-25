//--------------------
// kun 2025.01.25
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "BaseEffectExecution.generated.h"

UCLASS(MinimalAPI, Blueprintable, Abstract)
class UBaseEffectExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:
	virtual void GetValidScopedModifierAttributeCaptureDefinitions(OUT TArray<FGameplayEffectAttributeCaptureDefinition>& OutScopableModifiers) const override;
	virtual const FGameplayTagContainer& GetValidTransientAggregatorIdentifiers() const override;
	virtual bool DoesRequirePassedInTags() const override;
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
