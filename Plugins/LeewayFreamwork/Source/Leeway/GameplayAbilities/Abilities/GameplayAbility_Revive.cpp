//--------------------
// kun 2025.02.04
//--------------------

#include "GameplayAbility_Revive.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Leeway/Actor/Character/BaseCharacter.h"
#include "Leeway/GameFramework/LWGameplayTags.h"
#include "Leeway/GameFramework/BasePlayerState.h"

UGameplayAbility_Revive::UGameplayAbility_Revive(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    if (HasAnyFlags(RF_ClassDefaultObject))
    {
        ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
        InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
        NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;

        FAbilityTriggerData TriggerData;
        TriggerData.TriggerTag = FLWGameplayTags::Get().GameEvent.Revive;
        TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
        AbilityTriggers.Add(TriggerData);

        // 死亡流程不cancel该GA;
        AbilityTags.AddTag(FLWGameplayTags::Get().GALabel.IgnoreToDeath);
        AbilityTags.AddTag(FLWGameplayTags::Get().GALabel.IgnoreToUninitial);
    }
}

void UGameplayAbility_Revive::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    float ReviveWaitTime = TriggerEventData ? TriggerEventData->EventMagnitude : 0;
    if (ReviveWaitTime > 0)
    {
        auto* DelayTask = UAbilityTask_WaitDelay::WaitDelay(this, ReviveWaitTime);
        DelayTask->OnFinish.AddDynamic(this, &ThisClass::K2_EndAbility);
        DelayTask->ReadyForActivation();
    }
    else
    {
        GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::K2_EndAbility);
    }

    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGameplayAbility_Revive::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    if (!bWasCancelled)
    {
        if (HasAuthority(&CurrentActivationInfo))
        {
            if (ABasePlayerState* PlayerState = Cast<ABasePlayerState>(GetOwningActorFromActorInfo()))
            {
                auto* PC = PlayerState->GetPlayerController();
                GetWorld()->GetTimerManager().SetTimerForNextTick(PC, &APlayerController::ServerRestartPlayer_Implementation);
            }
        }
    }
    else
    {
        ensure(false);
        UE_LOGD2();
    }

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
