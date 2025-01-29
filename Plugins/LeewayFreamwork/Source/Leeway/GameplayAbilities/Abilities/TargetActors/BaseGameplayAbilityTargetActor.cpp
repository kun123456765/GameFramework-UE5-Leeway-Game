//--------------------
// kun 2025.01.26
//--------------------

#include "BaseGameplayAbilityTargetActor.h"



void ABaseGameplayAbilityTargetActor::BPConfirmTargeting()
{
    ConfirmTargeting();
}

void ABaseGameplayAbilityTargetActor::StartTargeting(UGameplayAbility* InAbility)
{
    Super::StartTargeting(InAbility);
    SourceActor = InAbility->GetCurrentActorInfo()->AvatarActor.Get();
    ActorTargetingContainer.Owner = this;
    SceneQueryIgnoreActors.Emplace(SourceActor.Get());
    SceneQueryIgnoreActors.Emplace(this);
}

void ABaseGameplayAbilityTargetActor::ConfirmTargeting()
{
    Super::ConfirmTargeting();
}

const TArray<TWeakObjectPtr<AActor>>& ABaseGameplayAbilityTargetActor::GetSceneQueryIgnoreActors() const
{
    return SceneQueryIgnoreActors;
}