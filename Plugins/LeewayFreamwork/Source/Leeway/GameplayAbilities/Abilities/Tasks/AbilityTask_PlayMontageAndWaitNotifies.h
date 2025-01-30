//--------------------
// kun 2025.01.23
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "PlayMontageCallbackProxy.h"
#include "AbilityTask_PlayMontageAndWaitNotifies.generated.h"

USTRUCT(BlueprintType)
struct FPlayMontageDelegates
{
	GENERATED_USTRUCT_BODY()

	// Called when Montage finished playing and wasn't interrupted
	UPROPERTY(BlueprintAssignable, EditAnywhere)
	FOnMontagePlayDelegate OnCompleted;

	// Called when Montage starts blending out and is not interrupted
	UPROPERTY(BlueprintAssignable, EditAnywhere)
	FOnMontagePlayDelegate OnBlendOut;

	// Called when Montage has been interrupted (or failed to play)
	UPROPERTY(BlueprintAssignable, EditAnywhere)
	FOnMontagePlayDelegate OnInterrupted;

	UPROPERTY(BlueprintAssignable, EditAnywhere)
	FOnMontagePlayDelegate OnNotifyBegin;

	UPROPERTY(BlueprintAssignable, EditAnywhere)
	FOnMontagePlayDelegate OnNotifyEnd;
};


UCLASS(MinimalAPI, Blueprintable)
class UAbilityTask_PlayMontageAndWaitNotifies : public UAbilityTask
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FMontageWaitSimpleDelegate	OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FMontageWaitSimpleDelegate	OnBlendOut;

	UPROPERTY(BlueprintAssignable)
	FMontageWaitSimpleDelegate	OnInterrupted;

	UPROPERTY(BlueprintAssignable)
	FMontageWaitSimpleDelegate	OnCancelled;

	UPROPERTY(BlueprintAssignable)
	FPlayMontageAnimNotifyDelegate OnNotifyBegin;
	
	UPROPERTY(BlueprintAssignable)
	FPlayMontageAnimNotifyDelegate OnNotifyEnd;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "PlayMontageAndWaitNotifies",
		HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_PlayMontageAndWaitNotifies* CreatePlayMontageAndWaitProxy(UGameplayAbility* OwningAbility
		//, FPlayMontageDelegates& OutDelegates
		//, UPlayMontageCallbackProxy*& OutPlayMontageProxy
		, FName TaskInstanceName
		, UAnimMontage* MontageToPlay
		, float Rate = 1.f
		, FName StartSection = NAME_None
		, bool bStopWhenAbilityEnds = true
		, float AnimRootMotionTranslationScale = 1.f
		, float StartTimeSeconds = 0.f
		, bool bAllowInterruptAfterBlendOut = false
		);

private:
	void InitTask_PlayMontageAndWaitNotifies(UGameplayAbility* OwningAbility
		, UAnimMontage* MontageToPlay
		, float Rate
		, FName StartSection
		, bool bStopWhenAbilityEnds
		, float AnimRootMotionTranslationScale
		, float StartTimeSeconds
		, bool bAllowInterruptAfterBlendOut);

public:
	UFUNCTION()
	void OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	void OnGameplayAbilityCancelled();
	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	void OnNotifyBeginReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);
	UFUNCTION()
	void OnNotifyEndReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload);

	virtual void Activate() override;
	virtual void ExternalCancel() override;
	virtual FString GetDebugString() const override;

protected:
	virtual void OnDestroy(bool AbilityEnded) override;
	bool StopPlayingMontage();

private:

	//FPlayMontageDelegates Delegates;
	//TObjectPtr<UPlayMontageCallbackProxy> PlayMontageProxy;

	FOnMontageBlendingOutStarted BlendingOutDelegate;
	FOnMontageEnded MontageEndedDelegate;
	FDelegateHandle InterruptedHandle;

	UPROPERTY()
	TObjectPtr<UAnimMontage> MontageToPlay;

	UPROPERTY()
	float Rate;

	UPROPERTY()
	FName StartSection;

	UPROPERTY()
	float AnimRootMotionTranslationScale;

	UPROPERTY()
	float StartTimeSeconds;

	UPROPERTY()
	bool bStopWhenAbilityEnds;

	UPROPERTY()
	bool bAllowInterruptAfterBlendOut;
};
