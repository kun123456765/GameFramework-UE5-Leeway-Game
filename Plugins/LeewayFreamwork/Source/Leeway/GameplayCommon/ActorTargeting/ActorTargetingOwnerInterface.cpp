//--------------------
// kun 2025.01.26
//--------------------

#include "ActorTargetingOwnerInterface.h"
#include "Abilities/GameplayAbility.h"
#include "BaseActorTargeting.h"

void IActorTargetingOwnerInterface::PerformTargeting(FActorTargetingOwnerContext& OwnerContext)
{
    for (auto& ActorTargetingClass : GetActorTargetingContainer().ActorTargetingQueue)
    {
        auto* CDO = Cast<UBaseActorTargeting>(ActorTargetingClass.GetDefaultObject());
        CDO->PerformTargeting(OwnerContext);
    }
}
