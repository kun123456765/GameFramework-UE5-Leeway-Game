//--------------------
// kun 2025.02.06
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseBlackboardComponent.generated.h"

class ABaseCharacter;

UCLASS(ClassGroup = AI, meta = (BlueprintSpawnableComponent), hidecategories = (Sockets, Collision), MinimalAPI)
class UBaseBlackboardComponent : public UBlackboardComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Leeway|AI|Components|Blackboard")
	class ABaseCharacter* GetValueAsBaseCharacter(const FName& KeyName) const;

	UFUNCTION(BlueprintCallable, Category = "Leeway|AI|Components|Blackboard")
	void SetValueAsBaseCharacter(const FName& KeyName, ABaseCharacter* ObjectValue);

	UFUNCTION(BlueprintCallable, Category = "Leeway|AI|Components|Blackboard")
	const struct FGameplayAbilitySpecHandle& GetValueAsGameplayAbilitySpecHandle(const FName& KeyName) const;

	UFUNCTION(BlueprintCallable, Category = "Leeway|AI|Components|Blackboard")
	void SetValueAsGameplayAbilitySpecHandle(const FName& KeyName, FGameplayAbilitySpecHandle ObjectValue);

	UFUNCTION(BlueprintCallable, Category = "Leeway|AI|Components|Blackboard")
	const struct FGameplayTag& GetValueAsGameplayTag(const FName& KeyName) const;

	UFUNCTION(BlueprintCallable, Category = "Leeway|AI|Components|Blackboard")
	void SetValueAsGameplayTag(const FName& KeyName, FGameplayTag ObjectValue);

public:
	template<class TDataClass>
	typename const TDataClass::FDataType& GetValueRef(FBlackboard::FKey KeyID) const;
};

template<class TDataClass>
typename const TDataClass::FDataType& UBaseBlackboardComponent::GetValueRef(FBlackboard::FKey KeyID) const
{
	const FBlackboardEntry* EntryInfo = GetBlackboardAsset() ? GetBlackboardAsset()->GetKey(KeyID) : nullptr;
	if ((EntryInfo == nullptr) || (EntryInfo->KeyType == nullptr) || (EntryInfo->KeyType->GetClass() != TDataClass::StaticClass()))
	{
		return TDataClass::InvalidValue;
	}

	UBlackboardKeyType* KeyOb = EntryInfo->KeyType->HasInstance() ? KeyInstances[KeyID] : EntryInfo->KeyType;
	const uint16 DataOffset = EntryInfo->KeyType->HasInstance() ? sizeof(FBlackboardInstancedKeyMemory) : 0;

	const uint8* RawData = GetKeyRawData(KeyID) + DataOffset;
	return RawData ? TDataClass::GetValueRef((TDataClass*)KeyOb, RawData) : TDataClass::InvalidValue;
}
