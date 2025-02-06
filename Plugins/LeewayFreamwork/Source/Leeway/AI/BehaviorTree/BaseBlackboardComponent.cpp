//--------------------
// kun 2025.02.06
//--------------------

#include "BaseBlackboardComponent.h"
#include "Leeway/AI/BehaviorTree/Blackboard/BlackboardKeyType_BaseCharacter.h"

ABaseCharacter* UBaseBlackboardComponent::GetValueAsBaseCharacter(const FName& KeyName) const
{
	return GetValue<UBlackboardKeyType_BaseCharacter>(KeyName);
}

void UBaseBlackboardComponent::SetValueAsBaseCharacter(const FName& KeyName, ABaseCharacter* ObjectValue)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	SetValue<UBlackboardKeyType_BaseCharacter>(KeyID, ObjectValue);
}
