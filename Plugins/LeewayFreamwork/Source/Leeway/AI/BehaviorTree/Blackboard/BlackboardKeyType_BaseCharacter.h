//--------------------
// kun 2025.02.06
//--------------------

#pragma once

#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BlackboardKeyType_BaseCharacter.generated.h"

#undef LW_BBKEY_TYPE_OBJECT_CLASS
#define LW_BBKEY_TYPE_OBJECT_CLASS ABaseCharacter
class LW_BBKEY_TYPE_OBJECT_CLASS;

UCLASS(EditInlineNew, meta = (DisplayName = "LWBaseCharacter"), MinimalAPI)
class UBlackboardKeyType_BaseCharacter : public UBlackboardKeyType
{
	GENERATED_UCLASS_BODY()
	
	typedef LW_BBKEY_TYPE_OBJECT_CLASS* FDataType;
	static const FDataType InvalidValue;

	UPROPERTY(Category = Blackboard, EditDefaultsOnly, NoClear, meta = (AllowAbstract = "1"))
	TObjectPtr<UClass> BaseClass;

	static FDataType GetValue(const UBlackboardKeyType_BaseCharacter* KeyOb, const uint8* RawData);
	static bool SetValue(UBlackboardKeyType_BaseCharacter* KeyOb, uint8* RawData, FDataType Value);

	virtual EBlackboardCompare::Type CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock,
		const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const override;

	virtual FString DescribeSelf() const override;
	virtual bool IsAllowedByFilter(UBlackboardKeyType* FilterOb) const override;

protected:
	virtual FString DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const override;
	virtual bool GetLocation(const UBlackboardComponent& OwnerComp, const uint8* RawData, FVector& Location) const override;
	virtual bool GetRotation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, FRotator& Rotation) const override;
	virtual bool TestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const override;
};
