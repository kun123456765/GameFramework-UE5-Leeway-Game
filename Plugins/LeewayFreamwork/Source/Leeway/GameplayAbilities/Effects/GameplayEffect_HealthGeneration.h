//--------------------
// kun 2025.02.02
//--------------------

#pragma once

#include "BaseGameplayEffect.h"
#include "GameplayEffect_HealthGeneration.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class UGameplayEffect_HealthGeneration : public UBaseGameplayEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float DamageIntervalWorldTime = 5.f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float ActivationRatio = 0.5f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float InhibitionRatio = 1.f;
};
