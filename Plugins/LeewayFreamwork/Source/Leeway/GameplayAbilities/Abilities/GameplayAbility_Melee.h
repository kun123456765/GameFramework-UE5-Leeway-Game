//--------------------
// kun 2025.01.23
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbility_Attack.h"
#include "GameplayAbility_Melee.generated.h"

USTRUCT(BlueprintType)
struct FAutoTargetingParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Radius = 300;
};

UCLASS(MinimalAPI, Blueprintable)
class UGameplayAbility_Melee : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UFUNCTION(BlueprintCallable)
	void OnTakeDamage(const FGameplayTag& TriggerTag, const FGameplayAbilityTargetDataHandle& TargetData);

	UFUNCTION()
	virtual void OnTimer_Tick();

protected:
	void UpdateWarpTarget();

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FAutoTargetingParams AutoTargetingParams;

protected:
	FTimerHandle TickTimer;
	TWeakObjectPtr<AActor> MotionWarpingTargetActor;
};
