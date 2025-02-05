//--------------------
// kun 2024.12.22
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "Leeway/Actor/Character/BaseCharacter.h"
#include "BasePlayer.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class ABasePlayer : public ABaseCharacter
{
    GENERATED_BODY()

public:
    ABasePlayer(const FObjectInitializer& ObjectInitializer);

public:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void Tick(float DeltaSeconds) override;
    virtual void OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState) override;
    virtual void PossessedBy(AController* NewController) override;
    virtual void UnPossessed() override;

protected:
    virtual void OnPlayerStateChangedImpl(APlayerState* NewPlayerState, APlayerState* OldPlayerState);
};
