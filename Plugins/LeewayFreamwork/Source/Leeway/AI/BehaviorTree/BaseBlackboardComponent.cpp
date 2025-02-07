//--------------------
// kun 2025.02.06
//--------------------

#include "BaseBlackboardComponent.h"
#include "GameplayAbilitySpecHandle.h"
#include "Leeway/AI/BehaviorTree/Blackboard/BlackboardKeyType_BaseCharacter.h"
#include "Leeway/AI/BehaviorTree/Blackboard/BlackboardKeyType_GameplayAbilitySpecHandle.h"
#include "Leeway/AI/BehaviorTree/Blackboard/BlackboardKeyType_GameplayTag.h"

ABaseCharacter* UBaseBlackboardComponent::GetValueAsBaseCharacter(const FName& KeyName) const
{
	return GetValue<UBlackboardKeyType_BaseCharacter>(KeyName);
}

void UBaseBlackboardComponent::SetValueAsBaseCharacter(const FName& KeyName, ABaseCharacter* ObjectValue)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	SetValue<UBlackboardKeyType_BaseCharacter>(KeyID, ObjectValue);
}

const FGameplayAbilitySpecHandle& UBaseBlackboardComponent::GetValueAsGameplayAbilitySpecHandle(const FName& KeyName) const
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	return GetValueRef<UBlackboardKeyType_GameplayAbilitySpecHandle>(KeyID);
}

void UBaseBlackboardComponent::SetValueAsGameplayAbilitySpecHandle(const FName& KeyName, FGameplayAbilitySpecHandle ObjectValue)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	SetValue<UBlackboardKeyType_GameplayAbilitySpecHandle>(KeyID, ObjectValue);
}

const FGameplayTag& UBaseBlackboardComponent::GetValueAsGameplayTag(const FName& KeyName) const
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	return GetValueRef<UBlackboardKeyType_GameplayTag>(KeyID);
}

void UBaseBlackboardComponent::SetValueAsGameplayTag(const FName& KeyName, FGameplayTag ObjectValue)
{
	const FBlackboard::FKey KeyID = GetKeyID(KeyName);
	SetValue<UBlackboardKeyType_GameplayTag>(KeyID, ObjectValue);
}
