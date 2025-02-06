//--------------------
// kun 2025.02.06
//--------------------

#include "LWBTFunctionLibrary.h"
#include "Misc/RuntimeErrors.h"
#include "BehaviorTree/BTNode.h"
#include "BlueprintNodeHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Leeway/Actor/BaseActor.h"
#include "Leeway/Actor/Character/BaseCharacter.h"
#include "Leeway/AI/BehaviorTree/BaseBehaviorTreeComponent.h"
#include "Leeway/AI/BehaviorTree/Blackboard/BlackboardKeyType_BaseCharacter.h"

ABaseCharacter* ULWBTFunctionLibrary::GetBlackboardValueAsBaseCharacter(UBTNode* NodeOwner, const FBlackboardKeySelector& Key)
{
	if (UBlackboardComponent* BlackboardComp = GetOwnersBlackboard(NodeOwner))
	{
		return Cast<ABaseCharacter>(BlackboardComp->GetValueAsObject(Key.SelectedKeyName));
	}
	return nullptr;
}
