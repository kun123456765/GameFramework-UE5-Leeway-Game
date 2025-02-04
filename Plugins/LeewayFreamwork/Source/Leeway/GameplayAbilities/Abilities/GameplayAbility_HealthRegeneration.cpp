//--------------------
// kun 2025.02.02
//--------------------

#include "GameplayAbility_HealthRegeneration.h"
#include "Leeway/GameplayAbilities/AttributeSets/CombatAttributeSet.h"

UGameplayAbility_HealthRegeneration::UGameplayAbility_HealthRegeneration(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
    InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
    NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerInitiated;
}

void UGameplayAbility_HealthRegeneration::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (PeriodicHealingEffect.Get())
    {
        GEHandle = ApplyGameplayEffectToOwner(Handle, ActorInfo, ActivationInfo, PeriodicHealingEffect.GetDefaultObject(), 1, 1);
        auto* ASC = GetAbilitySystemComponentFromActorInfo();
        GEHandle = ASC->SetActiveGameplayEffectInhibit(MoveTemp(GEHandle), true, false);
        FGameplayTag DataTag;
        float Magnitude = 0;
        FetchSetByCallerMagnitude(DataTag, Magnitude);
        ASC->UpdateActiveGameplayEffectSetByCallerMagnitude(GEHandle, DataTag, Magnitude);
        GetWorld()->GetTimerManager().SetTimer(CheckInhibitionTimer, FTimerDelegate::CreateUObject(this, &ThisClass::OnTimer_CheckInhibition), 1, true);
    }

    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGameplayAbility_HealthRegeneration::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    GetWorld()->GetTimerManager().ClearTimer(CheckInhibitionTimer);

    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_HealthRegeneration::FetchSetByCallerMagnitude_Implementation(FGameplayTag& GameplayTag, float& Magnitude) const
{
    Magnitude = 1.f;
}

void UGameplayAbility_HealthRegeneration::OnTimer_CheckInhibition()
{
    auto* ASC = GetAbilitySystemComponentFromActorInfo();
    auto* CombatSet = Cast<UCombatAttributeSet>(ASC->GetAttributeSet(UCombatAttributeSet::StaticClass()));
    float Now = GetWorld()->GetTime().GetWorldTimeSeconds();
    float Last = CombatSet->LastDamageWorldTime;

    if (Now - Last > DamageIntervalWorldTime)
    {
        if (auto* GEInstance = ASC->GetActiveGameplayEffect(GEHandle))
        {
            float HealthRatio = CombatSet->GetHealth() / CombatSet->GetMaxHealth();
            if (GEInstance->bIsInhibited)
            {
                if (HealthRatio < ActivationEffectRatio)
                {
                    GEHandle = ASC->SetActiveGameplayEffectInhibit(MoveTemp(GEHandle), false, true);
                }
            }
            else
            {
                if (HealthRatio >= InhibitionEffectRatio)
                {
                    GEHandle = ASC->SetActiveGameplayEffectInhibit(MoveTemp(GEHandle), true, true);
                }
            }
        }
    }
}
