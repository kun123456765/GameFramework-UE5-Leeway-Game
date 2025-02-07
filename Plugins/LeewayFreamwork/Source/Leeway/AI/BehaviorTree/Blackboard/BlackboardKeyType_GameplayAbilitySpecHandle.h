//--------------------
// kun 2025.02.06
//--------------------

#pragma once

#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BlackboardKeyType_GameplayAbilitySpecHandle.generated.h"

#undef LW_BBKEY_TYPE_STRUCT
#define LW_BBKEY_TYPE_STRUCT FGameplayAbilitySpecHandle
struct LW_BBKEY_TYPE_STRUCT;

UCLASS(EditInlineNew, meta = (DisplayName = "LWGameplayAbilitySpecHandle"), MinimalAPI)
class UBlackboardKeyType_GameplayAbilitySpecHandle : public UBlackboardKeyType
{
	GENERATED_UCLASS_BODY()
	
	typedef LW_BBKEY_TYPE_STRUCT FDataType;
	static const FDataType InvalidValue;

	static const FDataType& GetValueRef(const UBlackboardKeyType_GameplayAbilitySpecHandle* KeyOb, const uint8* RawData);
	static FDataType GetValue(const UBlackboardKeyType_GameplayAbilitySpecHandle* KeyOb, const uint8* RawData);
	static bool SetValue(UBlackboardKeyType_GameplayAbilitySpecHandle* KeyOb, uint8* RawData, FDataType Value);

	virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock,
		const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;

	virtual FString DescribeSelf() const override;

protected:
	virtual void InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock) override;
	virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;
	virtual bool TestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const override;
};
