//--------------------
// kun 2025.01.04
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BaseAbilitySystemComponent.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class UBaseAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

#if false
public:
	virtual void ForceAvatarReplication();
	virtual void SetReplicationMode(EGameplayEffectReplicationMode NewReplicationMode);
	virtual IAbilitySystemReplicationProxyInterface* GetReplicationInterface();
	virtual bool IsOwnerActorAuthoritative() const;
	virtual bool ShouldRecordMontageReplication() const;
	virtual void ReplicateEndOrCancelAbility(FGameplayAbilitySpecHandle Handle, FGameplayAbilityActivationInfo ActivationInfo, UGameplayAbility* Ability, bool bWasCanceled);
	virtual void ForceCancelAbilityDueToReplication(UGameplayAbility* Instance);
	virtual FActiveGameplayEffectHandle ApplyGameplayEffectSpecToTarget(const FGameplayEffectSpec& GameplayEffect, UAbilitySystemComponent* Target, FPredictionKey PredictionKey = FPredictionKey());
	virtual FActiveGameplayEffectHandle ApplyGameplayEffectSpecToSelf(const FGameplayEffectSpec& GameplayEffect, FPredictionKey PredictionKey = FPredictionKey());
	virtual bool RemoveActiveGameplayEffect(FActiveGameplayEffectHandle Handle, int32 StacksToRemove = -1);
	virtual void RemoveActiveGameplayEffectBySourceEffect(TSubclassOf<UGameplayEffect> GameplayEffect, UAbilitySystemComponent* InstigatorAbilitySystemComponent, int32 StacksToRemove = -1);
	virtual FGameplayEffectSpecHandle MakeOutgoingSpec(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, FGameplayEffectContextHandle Context) const;
	virtual FGameplayEffectContextHandle MakeEffectContext() const;
	virtual void OnPredictiveGameplayCueCatchup(FGameplayTag Tag);
	virtual void RecomputeGameplayEffectStartTimes(const float WorldTime, const float ServerWorldTime);
	virtual void UpdateActiveGameplayEffectSetByCallerMagnitude(FActiveGameplayEffectHandle ActiveHandle, FGameplayTag SetByCallerTag, float NewValue);
	virtual void UpdateActiveGameplayEffectSetByCallerMagnitudes(FActiveGameplayEffectHandle ActiveHandle, const TMap<FGameplayTag, float>& NewSetByCallerValues);
	virtual void SetActiveGameplayEffectLevel(FActiveGameplayEffectHandle ActiveHandle, int32 NewLevel);
	virtual void SetActiveGameplayEffectLevelUsingQuery(FGameplayEffectQuery Query, int32 NewLevel);
	virtual void InhibitActiveGameplayEffect(FActiveGameplayEffectHandle ActiveGEHandle, bool bInhibit, bool bInvokeGameplayCueEvents);
	virtual FActiveGameplayEffectHandle SetActiveGameplayEffectInhibit(FActiveGameplayEffectHandle&& ActiveGEHandle, bool bInhibit, bool bInvokeGameplayCueEvents);
	virtual void OnGameplayEffectDurationChange(struct FActiveGameplayEffect& ActiveEffect);
	virtual void NotifyAbilityCommit(UGameplayAbility* Ability);
	virtual void NotifyAbilityActivated(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability);
	virtual void NotifyAbilityFailed(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, const FGameplayTagContainer& FailureReason);
	virtual int32 HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload);
	virtual void ModifyActiveEffectStartTime(FActiveGameplayEffectHandle Handle, float StartTimeDiff);
	virtual int32 RemoveActiveEffects(const FGameplayEffectQuery& Query, int32 StacksToRemove = -1);
	virtual void InitDefaultGameplayCueParameters(FGameplayCueParameters& Parameters);
	virtual bool IsReadyForGameplayCues();
	virtual void HandleDeferredGameplayCues(const FActiveGameplayEffectsContainer* GameplayEffectsContainer);
	virtual void ReinvokeActiveGameplayCues();
	virtual void DestroyActiveState();
	virtual void ApplyAbilityBlockAndCancelTags(const FGameplayTagContainer& AbilityTags, UGameplayAbility* RequestingAbility, bool bEnableBlockTags, const FGameplayTagContainer& BlockTags, bool bExecute);
	virtual void HandleChangeAbilityCanBeCanceled(const FGameplayTagContainer& AbilityTags, UGameplayAbility* RequestingAbility, bool bCanBeCanceled);
	virtual bool AreAbilityTagsBlocked(const FGameplayTagContainer& Tags) const;
	virtual void FindAllAbilitySpecsFromInputID(int32 InputID, TArray<const FGameplayAbilitySpec*>& OutAbilitySpecs) const;
	virtual FGameplayAbilitySpec BuildAbilitySpecFromClass(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level = 0, int32 InputID = -1);
	virtual void NotifyAbilityEnded(FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, bool bWasCancelled);
	virtual void DisplayDebug(class UCanvas* Canvas, const class FDebugDisplayInfo& DebugDisplay, float& YL, float& YPos);
	virtual void PrintDebug();
	virtual void Debug_Internal(struct FAbilitySystemComponentDebugInfo& Info);
	virtual void OnServerPrintDebug_Request();
	virtual bool ShouldSendClientDebugStringsToServer() const;
	virtual void OnClientPrintDebug_Response(const TArray<FString>& Strings, int32 GameFlags);
	virtual void GrabDebugSnapshot(FVisualLogEntry* Snapshot) const;
	virtual void OnRep_ClientDebugString();
	virtual void OnRep_ServerDebugString();
	virtual bool ShouldDoServerAbilityRPCBatch() const;
	virtual void BeginServerAbilityRPCBatch(FGameplayAbilitySpecHandle AbilityHandle);
	virtual void EndServerAbilityRPCBatch(FGameplayAbilitySpecHandle AbilityHandle);
	virtual void ServerAbilityRPCBatch_Internal(FServerAbilityRPCBatch& BatchInfo);
	virtual void SetUserAbilityActivationInhibited(bool NewInhibit);
	virtual void BindToInputComponent(UInputComponent* InputComponent);
	virtual void BindAbilityActivationToInputComponent(UInputComponent* InputComponent, FGameplayAbilityInputBinds BindInfo);
	virtual void SetBlockAbilityBindingsArray(FGameplayAbilityInputBinds BindInfo);
	virtual void AbilityLocalInputPressed(int32 InputID);
	virtual void AbilityLocalInputReleased(int32 InputID);
	virtual void LocalInputConfirm();
	virtual void LocalInputCancel();
	virtual void TargetConfirm();
#endif
};
