//--------------------
// kun 2025.02.04
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "GameplayAbility_Death.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class UGameplayAbility_Death : public UBaseGameplayAbility
{
	GENERATED_BODY()
public:
    UGameplayAbility_Death(const FObjectInitializer& ObjectInitializer);
public:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

public:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    float DeadBodyRemainTime = 10.f;

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
    float ReviveWaitTime = 5.f;
};
