//--------------------
// kun 2025.02.02
//--------------------

#pragma once

#include "BaseGameplayAbility.h"
#include "GameplayAbility_HealthRegeneration.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class UGameplayAbility_HealthRegeneration : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:
    virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
    virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void FetchSetByCallerMagnitude(FGameplayTag& GameplayTag, float& Magnitude) const;

protected:
	UFUNCTION()
	void OnTimer_CheckInhibition();

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess="true"))
	float DamageIntervalWorldTime = 5.f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float ActivationEffectRatio = 0.5f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float InhibitionEffectRatio = 1.f;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UBaseGameplayEffect> PeriodicHealingEffect;

protected:
	FTimerHandle CheckInhibitionTimer;
	FActiveGameplayEffectHandle GEHandle;
};
