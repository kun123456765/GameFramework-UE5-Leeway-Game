//--------------------
// kun 2025.01.26
//--------------------

#pragma once

#include "UObject/Interface.h"
#include "Abilities/GameplayAbility.h"
#include "ActorTargetingContainer.h"
#include "ActorTargetingTypes.h"
#include "ActorTargetingOwnerInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UActorTargetingOwnerInterface : public UInterface
{
    GENERATED_BODY()
};

class IActorTargetingOwnerInterface
{
    GENERATED_BODY()

public:
    virtual const TArray<TWeakObjectPtr<AActor>>& GetSceneQueryIgnoreActors() const = 0;

protected:
    virtual FActorTargetingContainer& GetActorTargetingContainer() = 0;
    virtual void PerformTargeting(FActorTargetingOwnerContext& Context);
};
