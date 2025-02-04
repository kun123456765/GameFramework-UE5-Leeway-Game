//--------------------
// kun 2025.02.04
//--------------------

#include "GameplayAbility_Death.h"
#include "Leeway/Actor/Character/BaseCharacter.h"
#include "Leeway/Animation/LWAnimBlueprintLibrary.h"
#include "Leeway/GameFramework/LWGameplayTags.h"

UGameplayAbility_Death::UGameplayAbility_Death(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    if (HasAnyFlags(RF_ClassDefaultObject))
    {
        ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
        InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
        NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;

        FAbilityTriggerData TriggerData;
        TriggerData.TriggerTag = FLWGameplayTags::Get().GameEvent.Death;
        TriggerData.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
        AbilityTriggers.Add(TriggerData);
    }
}

void UGameplayAbility_Death::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    auto* ASC = GetAbilitySystemComponentFromActorInfo();
    FGameplayTagContainer AbilityTypesToIgnore;
    AbilityTypesToIgnore.AddTag(FLWGameplayTags::Get().GALabel.IgnoreToDeath);
    ASC->CancelAbilities(nullptr, &AbilityTypesToIgnore);

    if (auto* BaseCharacter = Cast<ABaseCharacter>(GetAvatarActorFromActorInfo()))
    {
        BaseCharacter->SetRagdollEnable(true);
    }

    if (auto* BaseCharacter = Cast<ABaseCharacter>(GetAvatarActorFromActorInfo()))
    {
        FGameplayEventData EventData;
        EventData.EventMagnitude = ReviveWaitTime;
        SendGameplayEvent(FLWGameplayTags::Get().GameEvent.Revive, EventData);
        BaseCharacter->DetachFromControllerPendingDestroy();
        BaseCharacter->SetLifeSpan(DeadBodyRemainTime);
        //BaseCharacter->SetRagdollEnable(false);
    }

    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGameplayAbility_Death::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
