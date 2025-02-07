//--------------------
// kun 2025.02.06
//--------------------

#include "BlackboardKeyType_GameplayTag.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BlackboardKeyType_GameplayTag)

const UBlackboardKeyType_GameplayTag::FDataType UBlackboardKeyType_GameplayTag::InvalidValue = FGameplayTag();

UBlackboardKeyType_GameplayTag::UBlackboardKeyType_GameplayTag(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	ValueSize = FDataType::StaticStruct()->GetStructureSize();
	SupportedOp = EBlackboardKeyOperation::Basic;
}

const UBlackboardKeyType_GameplayTag::FDataType& UBlackboardKeyType_GameplayTag::GetValueRef(const UBlackboardKeyType_GameplayTag* KeyOb, const uint8* RawData)
{
	return *(FDataType*)RawData;
}

UBlackboardKeyType_GameplayTag::FDataType UBlackboardKeyType_GameplayTag::GetValue(const UBlackboardKeyType_GameplayTag* KeyOb, const uint8* RawData)
{
	return GetValueFromMemory<FDataType>(RawData);
}

bool UBlackboardKeyType_GameplayTag::SetValue(UBlackboardKeyType_GameplayTag* KeyOb, uint8* RawData, FDataType Value)
{
	return SetValueInMemory<FDataType>(RawData, Value);
}

EBlackboardCompare::Type UBlackboardKeyType_GameplayTag::CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock,
	const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
{
	const FDataType& MyValue = GetValueRef(this, MemoryBlock);
	const FDataType& OtherValue = GetValueRef((UBlackboardKeyType_GameplayTag*)OtherKeyOb, OtherMemoryBlock);

	return MyValue == OtherValue ? EBlackboardCompare::Equal : EBlackboardCompare::NotEqual;
}

FString UBlackboardKeyType_GameplayTag::DescribeSelf() const
{
	return FDataType::StaticStruct()->GetName();
}

void UBlackboardKeyType_GameplayTag::InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock)
{
	SetValue(this, MemoryBlock, InvalidValue);
}

FString UBlackboardKeyType_GameplayTag::DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const
{
	return GetValueRef(this, RawData).ToString();
}

bool UBlackboardKeyType_GameplayTag::TestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const
{
	if (MemoryBlock == NULL)
	{
		return false;
	}

	bool bSet = GetValueRef(this, MemoryBlock).IsValid();
	return Op == EBasicKeyOperation::Set && bSet || Op == EBasicKeyOperation::NotSet && !bSet;
}
