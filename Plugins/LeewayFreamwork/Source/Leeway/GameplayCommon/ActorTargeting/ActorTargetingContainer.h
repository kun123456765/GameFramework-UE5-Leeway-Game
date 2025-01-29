//--------------------
// kun 2025.01.26
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "ActorTargetingContainer.generated.h"

class IActorTargetingOwnerInterface;
class UBaseActorTargeting;

USTRUCT(BlueprintType)
struct FActorTargetingContainer
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly, Transient)
    TScriptInterface<IActorTargetingOwnerInterface> Owner;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    TArray<TSubclassOf<UBaseActorTargeting>> ActorTargetingQueue;
};