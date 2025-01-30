//--------------------
// kun 2025.01.23
//--------------------

#include "AbilityTask_PlayMontageAndWaitNotifies.h"
#include "PlayMontageCallbackProxy.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemLog.h"
#include "AbilitySystemGlobals.h"

UAbilityTask_PlayMontageAndWaitNotifies* UAbilityTask_PlayMontageAndWaitNotifies::CreatePlayMontageAndWaitProxy(UGameplayAbility* OwningAbility
    //, FPlayMontageDelegates& OutDelegates
    //, UPlayMontageCallbackProxy*& OutPlayMontageProxy
    , FName TaskInstanceName
    , UAnimMontage* MontageToPlay
    , float Rate
    , FName StartSection
    , bool bStopWhenAbilityEnds
    , float AnimRootMotionTranslationScale
    , float StartTimeSeconds
    , bool bAllowInterruptAfterBlendOut)
{
    UAbilitySystemGlobals::NonShipping_ApplyGlobalAbilityScaler_Rate(Rate);

    UAbilityTask_PlayMontageAndWaitNotifies* MyObj = NewAbilityTask<UAbilityTask_PlayMontageAndWaitNotifies>(OwningAbility, TaskInstanceName);
    MyObj->InitTask_PlayMontageAndWaitNotifies(OwningAbility, MontageToPlay, Rate, StartSection, bStopWhenAbilityEnds, AnimRootMotionTranslationScale, StartTimeSeconds, bAllowInterruptAfterBlendOut);
    //OutPlayMontageProxy = MyObj->PlayMontageProxy;
    return MyObj;
}

void UAbilityTask_PlayMontageAndWaitNotifies::InitTask_PlayMontageAndWaitNotifies(UGameplayAbility* OwningAbility
    , UAnimMontage* InMontageToPlay
    , float InRate
    , FName InStartSection
    , bool InbStopWhenAbilityEnds
    , float InAnimRootMotionTranslationScale
    , float InStartTimeSeconds
    , bool InbAllowInterruptAfterBlendOut)
{
    //if (UAbilitySystemComponent* ASC = Cast<UAbilitySystemComponent>(GetGameplayTasksComponent()))
    //{
    //    const FGameplayAbilityActorInfo* ActorInfo = OwningAbility->GetCurrentActorInfo();
    //    UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
    //    if (AnimInstance != nullptr)
    //    {
    //        auto* SKMC = AnimInstance->GetSkelMeshComponent();
    //        UPlayMontageCallbackProxy* NewProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(SKMC, MontageToPlay, Rate, StartTimeSeconds, StartSection);
    //        //PlayMontageProxy = NewProxy;
    //    }
    //}

	MontageToPlay = InMontageToPlay;
	Rate = InRate;
	StartSection = InStartSection;
	bStopWhenAbilityEnds = InbStopWhenAbilityEnds;
	AnimRootMotionTranslationScale = InAnimRootMotionTranslationScale;
	StartTimeSeconds = InStartTimeSeconds;
	bAllowInterruptAfterBlendOut = InbAllowInterruptAfterBlendOut;
}

void UAbilityTask_PlayMontageAndWaitNotifies::OnMontageBlendingOut(UAnimMontage* Montage, bool bInterrupted)
{
	const bool bPlayingThisMontage = (Montage == MontageToPlay) && Ability && Ability->GetCurrentMontage() == MontageToPlay;
	if (bPlayingThisMontage)
	{
		// Reset AnimRootMotionTranslationScale
		ACharacter* Character = Cast<ACharacter>(GetAvatarActor());
		if (Character && (Character->GetLocalRole() == ROLE_Authority ||
			(Character->GetLocalRole() == ROLE_AutonomousProxy && Ability->GetNetExecutionPolicy() == EGameplayAbilityNetExecutionPolicy::LocalPredicted)))
		{
			Character->SetAnimRootMotionTranslationScale(1.f);
		}
	}

	if (bPlayingThisMontage && (bInterrupted || !bAllowInterruptAfterBlendOut))
	{
		if (UAbilitySystemComponent* ASC = AbilitySystemComponent.Get())
		{
			ASC->ClearAnimatingAbility(Ability);
		}
	}

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if (bInterrupted)
		{
			OnInterrupted.Broadcast();

			EndTask();
		}
		else
		{
			OnBlendOut.Broadcast();
		}
	}
}

void UAbilityTask_PlayMontageAndWaitNotifies::OnGameplayAbilityCancelled()
{
	if (StopPlayingMontage() || bAllowInterruptAfterBlendOut)
	{
		// Let the BP handle the interrupt as well
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnInterrupted.Broadcast();
		}
	}

	EndTask();
}

void UAbilityTask_PlayMontageAndWaitNotifies::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (!bInterrupted)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCompleted.Broadcast();
		}
	}

	EndTask();
}

void UAbilityTask_PlayMontageAndWaitNotifies::OnNotifyBeginReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnNotifyBegin.Broadcast(NotifyName, BranchingPointNotifyPayload);
	}
}

void UAbilityTask_PlayMontageAndWaitNotifies::OnNotifyEndReceived(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointNotifyPayload)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnNotifyEnd.Broadcast(NotifyName, BranchingPointNotifyPayload);
	}
}

void UAbilityTask_PlayMontageAndWaitNotifies::Activate()
{
	if (Ability == nullptr)
	{
		return;
	}

	bool bPlayedMontage = false;

	if (UAbilitySystemComponent* ASC = AbilitySystemComponent.Get())
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			if (ASC->PlayMontage(Ability, Ability->GetCurrentActivationInfo(), MontageToPlay, Rate, StartSection, StartTimeSeconds) > 0.f)
			{
				// Playing a montage could potentially fire off a callback into game code which could kill this ability! Early out if we are  pending kill.
				if (ShouldBroadcastAbilityTaskDelegates() == false)
				{
					return;
				}

				InterruptedHandle = Ability->OnGameplayAbilityCancelled.AddUObject(this, &UAbilityTask_PlayMontageAndWaitNotifies::OnGameplayAbilityCancelled);

				BlendingOutDelegate.BindUObject(this, &UAbilityTask_PlayMontageAndWaitNotifies::OnMontageBlendingOut);
				AnimInstance->Montage_SetBlendingOutDelegate(BlendingOutDelegate, MontageToPlay);

				MontageEndedDelegate.BindUObject(this, &UAbilityTask_PlayMontageAndWaitNotifies::OnMontageEnded);
				AnimInstance->Montage_SetEndDelegate(MontageEndedDelegate, MontageToPlay);

				AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &UAbilityTask_PlayMontageAndWaitNotifies::OnNotifyBeginReceived);
				AnimInstance->OnPlayMontageNotifyEnd.AddDynamic(this, &UAbilityTask_PlayMontageAndWaitNotifies::OnNotifyEndReceived);

				ACharacter* Character = Cast<ACharacter>(GetAvatarActor());
				if (Character && (Character->GetLocalRole() == ROLE_Authority ||
					(Character->GetLocalRole() == ROLE_AutonomousProxy && Ability->GetNetExecutionPolicy() == EGameplayAbilityNetExecutionPolicy::LocalPredicted)))
				{
					Character->SetAnimRootMotionTranslationScale(AnimRootMotionTranslationScale);
				}

				bPlayedMontage = true;
			}
		}
		else
		{
			ABILITY_LOG(Warning, TEXT("UAbilityTask_PlayMontageAndWaitNotifies call to PlayMontage failed!"));
		}
	}
	else
	{
		ABILITY_LOG(Warning, TEXT("UAbilityTask_PlayMontageAndWaitNotifies called on invalid AbilitySystemComponent"));
	}

	if (!bPlayedMontage)
	{
		ABILITY_LOG(Warning, TEXT("UAbilityTask_PlayMontageAndWaitNotifies called in Ability %s failed to play montage %s; Task Instance Name %s."), *Ability->GetName(), *GetNameSafe(MontageToPlay), *InstanceName.ToString());
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnCancelled.Broadcast();
		}
	}

	SetWaitingOnAvatar();
}

void UAbilityTask_PlayMontageAndWaitNotifies::ExternalCancel()
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnCancelled.Broadcast();
	}
	Super::ExternalCancel();
}

FString UAbilityTask_PlayMontageAndWaitNotifies::GetDebugString() const
{
	UAnimMontage* PlayingMontage = nullptr;
	if (Ability)
	{
		const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
		UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();

		if (AnimInstance != nullptr)
		{
			PlayingMontage = AnimInstance->Montage_IsActive(MontageToPlay) ? ToRawPtr(MontageToPlay) : AnimInstance->GetCurrentActiveMontage();
		}
	}

	return FString::Printf(TEXT("PlayMontageAndWait. MontageToPlay: %s  (Currently Playing): %s"), *GetNameSafe(MontageToPlay), *GetNameSafe(PlayingMontage));
}

void UAbilityTask_PlayMontageAndWaitNotifies::OnDestroy(bool AbilityEnded)
{
	// Note: Clearing montage end delegate isn't necessary since its not a multicast and will be cleared when the next montage plays.
	// (If we are destroyed, it will detect this and not do anything)

	// This delegate, however, should be cleared as it is a multicast
	if (Ability)
	{
		Ability->OnGameplayAbilityCancelled.Remove(InterruptedHandle);
		if (AbilityEnded && bStopWhenAbilityEnds)
		{
			StopPlayingMontage();
		}
	}

	Super::OnDestroy(AbilityEnded);
}

bool UAbilityTask_PlayMontageAndWaitNotifies::StopPlayingMontage()
{
	if (Ability == nullptr)
	{
		return false;
	}

	const FGameplayAbilityActorInfo* ActorInfo = Ability->GetCurrentActorInfo();
	if (ActorInfo == nullptr)
	{
		return false;
	}

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
	if (AnimInstance == nullptr)
	{
		return false;
	}

	// Check if the montage is still playing
	// The ability would have been interrupted, in which case we should automatically stop the montage
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
	if (ASC && Ability)
	{
		if (ASC->GetAnimatingAbility() == Ability
			&& ASC->GetCurrentMontage() == MontageToPlay)
		{
			// Unbind delegates so they don't get called as well
			FAnimMontageInstance* MontageInstance = AnimInstance->GetActiveInstanceForMontage(MontageToPlay);
			if (MontageInstance)
			{
				MontageInstance->OnMontageBlendingOutStarted.Unbind();
				MontageInstance->OnMontageEnded.Unbind();
			}

			ASC->CurrentMontageStop();
			return true;
		}
	}

	return false;
}
