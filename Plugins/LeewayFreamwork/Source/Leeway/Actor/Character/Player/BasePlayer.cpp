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
    if (auto* PS = Cast<ABasePlayerState>(GetPlayerState()))
    {
        if (auto* GameASC = Cast<UGameAbilitySystemComponent>(PS->GetAbilitySystemComponent()))
        {
            GameASC->SetAvatarActor(this);
            ASC = GameASC;
        }
    }
}

void ABasePlayer::UnPossessed()
{
    if (auto* PS = Cast<ABasePlayerState>(GetPlayerState()))
    {
        if (auto* ASComp = PS->GetAbilitySystemComponent())
        {
            ASComp->SetAvatarActor(this);
            ASC.Reset();
        }
    }

    Super::UnPossessed();
}

void ABasePlayer::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
