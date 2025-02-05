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

void ABasePlayer::OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState)
{
    OnPlayerStateChangedImpl(NewPlayerState, OldPlayerState);
}

void ABasePlayer::OnPlayerStateChangedImpl(APlayerState* NewPlayerState, APlayerState* OldPlayerState)
{
    auto* OldASC = OldPlayerState ? (OldPlayerState->Implements<UAbilitySystemInterface>() ? Cast<UBaseAbilitySystemComponent>(Cast<IAbilitySystemInterface>(OldPlayerState)->GetAbilitySystemComponent()) : nullptr) : nullptr;
    auto* CurASC = NewPlayerState ? (NewPlayerState->Implements<UAbilitySystemInterface>() ? Cast<UBaseAbilitySystemComponent>(Cast<IAbilitySystemInterface>(NewPlayerState)->GetAbilitySystemComponent()) : nullptr) : nullptr;

    if (OldASC != CurASC)
    {
        //todo kun 2025.01.31
        // how to reset the previous ability system component?
    }

    ChangeASC(CurASC);
}