//--------------------
// kun 2025.02.04
//--------------------

#pragma once

#include "Components/ActorComponent.h"
#include "BaseGameplayComponent.generated.h"


UCLASS(MinimalAPI, Blueprintable)
class UBaseGameplayComponent : public UActorComponent
{
    GENERATED_BODY()
public:
    UBaseGameplayComponent(const FObjectInitializer& ObjectInitializer);
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
