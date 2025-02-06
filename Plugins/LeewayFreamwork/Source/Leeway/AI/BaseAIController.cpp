//--------------------
// kun 2025.02.06
//--------------------

#include "BaseAIController.h"
#include "Leeway/AI/BehaviorTree/BaseBehaviorTreeComponent.h"
#include "Leeway/AI/BehaviorTree/BaseBlackboardComponent.h"

ABaseAIController::ABaseAIController(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    LWBehaviroTree = CreateDefaultSubobject<UBaseBehaviorTreeComponent>(TEXT("BaseBehaviorTreeComponent"));
    LWBlackboard = CreateDefaultSubobject<UBaseBlackboardComponent>(TEXT("BaseBlackboardComponent"));
}
