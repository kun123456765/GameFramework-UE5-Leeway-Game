//--------------------
// kun 2025.01.26
//--------------------

#pragma once

#include "UObject/Interface.h"
#include "ActorTargetingTypes.h"
#include "ActorTargetingInterface.generated.h"

struct FActorTargetingOwnerContext;

UINTERFACE(MinimalAPI, Blueprintable)
class UActorTargetingInterface : public UInterface
{
    GENERATED_BODY()
};

class IActorTargetingInterface
{
    GENERATED_BODY()

public:
    virtual void PerformTargeting(FActorTargetingOwnerContext& OwnerContext) = 0;
};
