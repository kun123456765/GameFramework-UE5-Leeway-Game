//--------------------
// kun 2024.12.22
//--------------------

#include "BasePlayer.h"
#include "Leeway/GameplayAbilities/BaseAbilitySystemComponent.h"
#include "Leeway/GameFramework/BasePlayerState.h"

ABasePlayer::ABasePlayer(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
}

void ABasePlayer::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ABasePlayer::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
}

void ABasePlayer::UnPossessed()
{
    Super::UnPossessed();
}

void ABasePlayer::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
