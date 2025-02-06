//--------------------
// kun 2025.02.06
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BaseBTTask.h"
#include "BTTask_TryActivateAbility.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class UBTTask_TryActivateAbility : public UBaseBTTask
{
    GENERATED_BODY()

public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
