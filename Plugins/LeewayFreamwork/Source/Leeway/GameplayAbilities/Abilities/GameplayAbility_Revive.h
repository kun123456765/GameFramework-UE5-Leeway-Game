//--------------------
// kun 2025.02.04
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "GameplayAbility_Revive.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class UGameplayAbility_Revive : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
    UGameplayAbility_Revive(const FObjectInitializer& ObjectInitializer);

public:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
};
