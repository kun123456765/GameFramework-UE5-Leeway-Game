//--------------------
// kun 2025.02.06
//--------------------

#include "BlackboardKeyType_GameplayAbilitySpecHandle.h"
#include "GameplayAbilitySpecHandle.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BlackboardKeyType_GameplayAbilitySpecHandle)

const UBlackboardKeyType_GameplayAbilitySpecHandle::FDataType UBlackboardKeyType_GameplayAbilitySpecHandle::InvalidValue = FGameplayAbilitySpecHandle();

UBlackboardKeyType_GameplayAbilitySpecHandle::UBlackboardKeyType_GameplayAbilitySpecHandle(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	ValueSize = FDataType::StaticStruct()->GetStructureSize();
	SupportedOp = EBlackboardKeyOperation::Basic;
}

const UBlackboardKeyType_GameplayAbilitySpecHandle::FDataType& UBlackboardKeyType_GameplayAbilitySpecHandle::GetValueRef(const UBlackboardKeyType_GameplayAbilitySpecHandle* KeyOb, const uint8* RawData)
{
	return *(FDataType*)RawData;
}

UBlackboardKeyType_GameplayAbilitySpecHandle::FDataType UBlackboardKeyType_GameplayAbilitySpecHandle::GetValue(const UBlackboardKeyType_GameplayAbilitySpecHandle* KeyOb, const uint8* RawData)
{
	return GetValueFromMemory<FDataType>(RawData);
}

bool UBlackboardKeyType_GameplayAbilitySpecHandle::SetValue(UBlackboardKeyType_GameplayAbilitySpecHandle* KeyOb, uint8* RawData, FDataType Value)
{
	return SetValueInMemory<FDataType>(RawData, Value);
}

EBlackboardCompare::Type UBlackboardKeyType_GameplayAbilitySpecHandle::CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock,
	const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
{
	const FDataType& MyValue = GetValueRef(this, MemoryBlock);
	const FDataType& OtherValue = GetValueRef((UBlackboardKeyType_GameplayAbilitySpecHandle*)OtherKeyOb, OtherMemoryBlock);

	return MyValue == OtherValue ? EBlackboardCompare::Equal : EBlackboardCompare::NotEqual;
}

FString UBlackboardKeyType_GameplayAbilitySpecHandle::DescribeSelf() const
{
	return FDataType::StaticStruct()->GetName();
}

void UBlackboardKeyType_GameplayAbilitySpecHandle::InitializeMemory(UBlackboardComponent& OwnerComp, uint8* MemoryBlock)
{
	SetValue(this, MemoryBlock, InvalidValue);
}

FString UBlackboardKeyType_GameplayAbilitySpecHandle::DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const
{
	return GetValueRef(this, RawData).ToString();
}

bool UBlackboardKeyType_GameplayAbilitySpecHandle::TestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const
{
	if (MemoryBlock == NULL)
	{
		return false;
	}

	bool bSet = GetValueRef(this, MemoryBlock).IsValid();
	return Op == EBasicKeyOperation::Set && bSet || Op == EBasicKeyOperation::NotSet && !bSet;
}
