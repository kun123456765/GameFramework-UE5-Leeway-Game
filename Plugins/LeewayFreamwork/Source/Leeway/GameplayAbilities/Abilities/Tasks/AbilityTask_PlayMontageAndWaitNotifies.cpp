//--------------------
// kun 2025.01.23
//--------------------

#include "AbilityTask_PlayMontageAndWaitNotifies.h"
#include "AbilitySystemComponent.h"
#include "PlayMontageCallbackProxy.h"
#include "AbilitySystemGlobals.h"

UAbilityTask_PlayMontageAndWaitNotifies* UAbilityTask_PlayMontageAndWaitNotifies::CreatePlayMontageAndWaitProxy(UGameplayAbility* OwningAbility
    , FPlayMontageDelegates& OutDelegates
    , UPlayMontageCallbackProxy*& OutPlayMontageProxy
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

    OutDelegates = MyObj->Delegates;
    OutPlayMontageProxy = MyObj->PlayMontageProxy;
    //MyObj->MontageToPlay = MontageToPlay;
    //MyObj->Rate = Rate;
    //MyObj->StartSection = StartSection;
    //MyObj->AnimRootMotionTranslationScale = AnimRootMotionTranslationScale;
    //MyObj->bStopWhenAbilityEnds = bStopWhenAbilityEnds;
    //MyObj->bAllowInterruptAfterBlendOut = bAllowInterruptAfterBlendOut;
    //MyObj->StartTimeSeconds = StartTimeSeconds;

    FPlayMontageDelegates Delegates;
    TObjectPtr<UPlayMontageCallbackProxy> PlayMontageProxy;
    return MyObj;
}

void UAbilityTask_PlayMontageAndWaitNotifies::InitTask_PlayMontageAndWaitNotifies(UGameplayAbility* OwningAbility
    , UAnimMontage* MontageToPlay
    , float Rate
    , FName StartSection
    , bool bStopWhenAbilityEnds
    , float AnimRootMotionTranslationScale
    , float StartTimeSeconds
    , bool bAllowInterruptAfterBlendOut)
{
    if (UAbilitySystemComponent* ASC = Cast<UAbilitySystemComponent>(GetGameplayTasksComponent()))
    {
        const FGameplayAbilityActorInfo* ActorInfo = OwningAbility->GetCurrentActorInfo();
        UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();
        if (AnimInstance != nullptr)
        {
            auto* SKMC = AnimInstance->GetSkelMeshComponent();
            UPlayMontageCallbackProxy* NewProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(SKMC, MontageToPlay, Rate, StartTimeSeconds, StartSection);
            PlayMontageProxy = NewProxy;
        }
    }
}
