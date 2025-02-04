//--------------------
// kun 2025.02.04
//--------------------

#pragma once

#include "BaseGameplayComponent.h"
#include "CharacterDeathComponent.generated.h"


UCLASS(MinimalAPI, Blueprintable)
class UCharacterDeathComponent : public UBaseGameplayComponent
{
    GENERATED_BODY()
public:
    UCharacterDeathComponent(const FObjectInitializer& ObjectInitializer);
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
