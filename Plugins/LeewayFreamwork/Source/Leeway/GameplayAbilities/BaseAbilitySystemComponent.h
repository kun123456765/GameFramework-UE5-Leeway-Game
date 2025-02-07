//--------------------
// kun 2025.01.04
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Engine/DataAsset.h"
#include "LWAbilitySystemDataAsset.h"
#include "BaseAbilitySystemComponent.generated.h"

DECLARE_DELEGATE_OneParam(FTriggerAbilityFromGameplayEventDelegate, const TArray<FGameplayAbilitySpecHandle>&);

UCLASS(MinimalAPI, Blueprintable, Abstract)
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

public:
	static FName AbilitySystemComponentName;

public:
    // note by kun 2025.01.24
    // 初始化使用的Actor的相关基本信息，GAS系统启动的入口;
	// 已存在的GA/GE并不会删除，但是会得知这个变化(OnAvatarSet);
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;
	// 清理使用的Actor相关;
	virtual void ClearActorInfo() override;

	// note by kun 2025.01.24
	// 监听GA执行情况的接口;
	virtual void NotifyAbilityCommit(UGameplayAbility* Ability) override;
	virtual void NotifyAbilityActivated(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability) override;
	virtual void NotifyAbilityFailed(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, const FGameplayTagContainer& FailureReason) override;

	//--------------------
	// note by kun 2025.01.25
	// montage相关的接口;

	virtual float PlayMontage(UGameplayAbility* AnimatingAbility, FGameplayAbilityActivationInfo ActivationInfo, UAnimMontage* Montage, float InPlayRate, FName StartSectionName = NAME_None, float StartTimeSeconds = 0.0f) override;
	virtual UAnimMontage* PlaySlotAnimationAsDynamicMontage(UGameplayAbility* AnimatingAbility, FGameplayAbilityActivationInfo ActivationInfo, UAnimSequenceBase* AnimAsset, FName SlotName, float BlendInTime, float BlendOutTime, float InPlayRate = 1.f, float StartTimeSeconds = 0.0f);

	/** Plays a montage without updating replication/prediction structures. Used by simulated proxies when replication tells them to play a montage. */
	virtual float PlayMontageSimulated(UAnimMontage* Montage, float InPlayRate, FName StartSectionName = NAME_None) override;

	virtual UAnimMontage* PlaySlotAnimationAsDynamicMontageSimulated(UAnimSequenceBase* AnimAsset, FName SlotName, float BlendInTime, float BlendOutTime, float InPlayRate = 1.f) override;

	/** Stops whatever montage is currently playing. Expectation is caller should only be stopping it if they are the current animating ability (or have good reason not to check) */
	virtual void CurrentMontageStop(float OverrideBlendOutTime = -1.0f) override;

	/** Stops current montage if it's the one given as the Montage param */
	virtual void StopMontageIfCurrent(const UAnimMontage& Montage, float OverrideBlendOutTime = -1.0f) override;

	/** Clear the animating ability that is passed in, if it's still currently animating */
	virtual void ClearAnimatingAbility(UGameplayAbility* Ability) override;

	/** Jumps current montage to given section. Expectation is caller should only be stopping it if they are the current animating ability (or have good reason not to check) */
	virtual void CurrentMontageJumpToSection(FName SectionName) override;

	/** Sets current montages next section name. Expectation is caller should only be stopping it if they are the current animating ability (or have good reason not to check) */
	virtual void CurrentMontageSetNextSectionName(FName FromSectionName, FName ToSectionName) override;

	/** Sets current montage's play rate */
	virtual void CurrentMontageSetPlayRate(float InPlayRate) override;
    virtual void OnRep_ReplicatedAnimMontage() override;
	//--------------------

public:
	void InitAbilitySystem(TObjectPtr<ULWAbilitySystemDataAsset> GrantedSet);
	void UninitAbilitySystem();

private:
	void InitGrantedByDataAsset(TObjectPtr<ULWAbilitySystemDataAsset> GrantedSet);
	void UninitAllGrantedAndInstancedObjects();
	
public:
	//--------------------
	// helpers
	//--------------------
	UFUNCTION(BlueprintCallable)
	int32 HandleGameplayEventBP(FGameplayTag EventTag, FGameplayEventData Payload);

	// note by kun 205.02.07
	// 扩展内部实现，增加TriggedAbilitySpecArray的Delegate
	// 配合FTriggerAbilityCallbackScope使用;
	virtual int32 HandleGameplayEvent(FGameplayTag EventTag, const FGameplayEventData* Payload) override;

private:
	FTriggerAbilityFromGameplayEventDelegate TriggerAbilityCallback;

private:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ULWAbilitySystemDataAsset> DA_AbilitySystem;

	bool bGrantedByInited = false;
	FGrantedSetHandle GrantedSetHandle;

	friend struct FTriggerAbilityCallbackScope;
};

// TriggedAbilitySpecArray的Delegate，特殊写法是为了防止误用;
struct FTriggerAbilityCallbackScope
{
	FTriggerAbilityCallbackScope(UBaseAbilitySystemComponent* InASC)
	{
		ASC = InASC;
		ASC->TriggerAbilityCallback.BindRaw(this, &FTriggerAbilityCallbackScope::OnCallback);
	}

	~FTriggerAbilityCallbackScope()
	{
		ASC->TriggerAbilityCallback.Unbind();
	}

private:
	void OnCallback(const TArray<FGameplayAbilitySpecHandle>& ActivatedHandles)
	{
		TriggerAbilityCallback.ExecuteIfBound(ActivatedHandles);
	}

	UBaseAbilitySystemComponent* ASC;

public:
	FTriggerAbilityFromGameplayEventDelegate TriggerAbilityCallback;
};
