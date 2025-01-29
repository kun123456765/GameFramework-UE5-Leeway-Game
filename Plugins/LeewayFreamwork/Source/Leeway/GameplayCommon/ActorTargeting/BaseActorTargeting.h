//--------------------
// kun 2025.01.26
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "ActorTargetingInterface.h"
#include "BaseActorTargeting.generated.h"

class IActorTargetingOwnerInterface;



UCLASS(MinimalAPI, Abstract, Const, DefaultToInstanced, EditInlineNew, CollapseCategories)
class UBaseActorTargeting : public UObject, public IActorTargetingInterface
{
    GENERATED_BODY()

public:
    UBaseActorTargeting();

public:
    virtual void PerformTargeting(FActorTargetingOwnerContext& OwnerContext) override PURE_VIRTUAL(UBaseActorTargeting::PerformTargeting, );
};
