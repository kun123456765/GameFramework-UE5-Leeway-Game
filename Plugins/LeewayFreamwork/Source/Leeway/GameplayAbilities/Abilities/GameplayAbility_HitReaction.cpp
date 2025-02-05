//--------------------
// kun 2025.01.23
//--------------------

#include "GameplayAbility_HitReaction.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "GameFramework/Character.h"
#include "Animation/AnimMontage.h"
#include "Leeway/Animation/LWAnimBlueprintLibrary.h"
#include "Leeway/Animation/AnimMetaData/LWAnimMetaData_HitReaction.h"
#include "Leeway/GameplayAbilities/Abilities/TargetActors/GATargetActor_MeleeWeapon.h"

UGameplayAbility_HitReaction::UGameplayAbility_HitReaction(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;
}

bool UGameplayAbility_HitReaction::ShouldAbilityRespondToEvent(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayEventData* Payload) const
{
    if (Super::ShouldAbilityRespondToEvent(ActorInfo, Payload))
    {
        if (Payload && Payload->TargetData.Num() && Payload->Instigator)
        {
            //if (const FGameplayAbilityTargetData_LW_OverlapMulti& TargetData = static_cast<FGameplayAbilityTargetData_LW_OverlapMulti>())
            //{
            //    if (TargetData.Overlaps.Num() > 0)
            //    {
            //        return true;
            //    }
            //}
            return true;
        }

        return false;
    }

    return false;
}

bool UGameplayAbility_HitReaction::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
{
    return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

void UGameplayAbility_HitReaction::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (!TriggerEventData)
    {
        return;
    }

    if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
    {
        return;
    }

    UAbilityTask_PlayMontageAndWait* AbilityTask_PlayMontageAndWait = nullptr;
    if (const auto* TargetData = static_cast<const FGameplayAbilityTargetData_LW_OverlapMulti*>(TriggerEventData->TargetData.Get(0)))
    {
        for (const auto& Overlap : TargetData->Overlaps)
        {
            if (Overlap.Actor.IsValid() && Overlap.Actor == ActorInfo->AvatarActor)
            {
                FName SectionName = ULWAnimBlueprintLibrary::ChooseFittestMontageSectionForHitReactionWithActor(AM_HitReaction, Cast<ACharacter>(Overlap.Actor.Get()), Cast<ACharacter>(TriggerEventData->Instigator), Overlap);
                auto* Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AM_HitReaction, 1.f, SectionName);
                Task->OnCompleted.AddDynamic(this, &ThisClass::K2_EndAbility);
                Task->OnBlendOut.AddDynamic(this, &ThisClass::K2_EndAbility);
                Task->OnInterrupted.AddDynamic(this, &ThisClass::K2_CancelAbility);
                //todo by kun 2025.02.01
                // ÐèÒªÂð?
                Task->OnCancelled.AddDynamic(this, &ThisClass::K2_CancelAbility);

                AbilityTask_PlayMontageAndWait = Task;
            }
        }
    }

    auto* DelayTask = UAbilityTask_WaitDelay::WaitDelay(this, 5.f);
    DelayTask->OnFinish.AddDynamic(this, &ThisClass::K2_EndAbility);

    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

    if (AbilityTask_PlayMontageAndWait)
    {
        AbilityTask_PlayMontageAndWait->ReadyForActivation();
        DelayTask->ReadyForActivation();
    }
}

void UGameplayAbility_HitReaction::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
