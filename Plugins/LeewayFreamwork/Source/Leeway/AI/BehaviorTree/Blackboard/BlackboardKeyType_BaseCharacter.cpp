//--------------------
// kun 2025.02.06
//--------------------

#include "BlackboardKeyType_BaseCharacter.h"
#include "Leeway/Actor/Character/BaseCharacter.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(BlackboardKeyType_BaseCharacter)

const UBlackboardKeyType_BaseCharacter::FDataType UBlackboardKeyType_BaseCharacter::InvalidValue = nullptr;

UBlackboardKeyType_BaseCharacter::UBlackboardKeyType_BaseCharacter(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
	ValueSize = sizeof(TWeakObjectPtr<FDataType>);
	BaseClass = LW_BBKEY_TYPE_OBJECT_CLASS::StaticClass();
	SupportedOp = EBlackboardKeyOperation::Basic;
}

UBlackboardKeyType_BaseCharacter::FDataType UBlackboardKeyType_BaseCharacter::GetValue(const UBlackboardKeyType_BaseCharacter* KeyOb, const uint8* RawData)
{
	if (RawData == NULL)
	{
		return NULL;
	}

	auto WeakObjPtr = GetValueFromMemory<TWeakObjectPtr<LW_BBKEY_TYPE_OBJECT_CLASS>>(RawData);
	return WeakObjPtr.Get();
}

bool UBlackboardKeyType_BaseCharacter::SetValue(UBlackboardKeyType_BaseCharacter* KeyOb, uint8* RawData, FDataType Value)
{
	TWeakObjectPtr<LW_BBKEY_TYPE_OBJECT_CLASS> WeakObjPtr(Value);
	return SetWeakObjectInMemory<LW_BBKEY_TYPE_OBJECT_CLASS>(RawData, WeakObjPtr);
}

EBlackboardCompare::Type UBlackboardKeyType_BaseCharacter::CompareValues(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock,
	const UBlackboardKeyType* OtherKeyOb, const uint8* OtherMemoryBlock) const
{
	const FDataType MyValue = GetValue(this, MemoryBlock);
	const FDataType OtherValue = GetValue((UBlackboardKeyType_BaseCharacter*)OtherKeyOb, OtherMemoryBlock);

	return (MyValue == OtherValue) ? EBlackboardCompare::Equal : EBlackboardCompare::NotEqual;
}

FString UBlackboardKeyType_BaseCharacter::DescribeValue(const UBlackboardComponent& OwnerComp, const uint8* RawData) const
{
	return *GetNameSafe(GetValue(this, RawData));
}

FString UBlackboardKeyType_BaseCharacter::DescribeSelf() const
{
	return *GetNameSafe(BaseClass);
}

bool UBlackboardKeyType_BaseCharacter::IsAllowedByFilter(UBlackboardKeyType* FilterOb) const
{
	UBlackboardKeyType_BaseCharacter* FilterObject = Cast<UBlackboardKeyType_BaseCharacter>(FilterOb);
	UE_CLOG(BaseClass == nullptr, LogTemp, Warning, TEXT("Cannot assign %s to a Blackboard Key with null base class. Should the base class be changed?"), FilterObject ? *FilterObject->DescribeSelf() : TEXT("NULL"));
	return (FilterObject && (FilterObject->BaseClass == BaseClass || (BaseClass != nullptr && BaseClass->IsChildOf(FilterObject->BaseClass))));
}

bool UBlackboardKeyType_BaseCharacter::GetLocation(const UBlackboardComponent& OwnerComp, const uint8* RawData, FVector& Location) const
{
	AActor* MyActor = Cast<AActor>(GetValue(this, RawData));
	if (MyActor)
	{
		Location = MyActor->GetActorLocation();
		return true;
	}

	return false;
}

bool UBlackboardKeyType_BaseCharacter::GetRotation(const UBlackboardComponent& OwnerComp, const uint8* RawData, FRotator& Rotation) const
{
	AActor* MyActor = Cast<AActor>(GetValue(this, RawData));
	if (MyActor)
	{
		Rotation = MyActor->GetActorRotation();
		return true;
	}

	return false;
}

bool UBlackboardKeyType_BaseCharacter::TestBasicOperation(const UBlackboardComponent& OwnerComp, const uint8* MemoryBlock, EBasicKeyOperation::Type Op) const
{
	if (MemoryBlock == NULL)
	{
		return false;
	}

	TWeakObjectPtr<LW_BBKEY_TYPE_OBJECT_CLASS> WeakObjPtr = GetValueFromMemory<TWeakObjectPtr<LW_BBKEY_TYPE_OBJECT_CLASS>>(MemoryBlock);
	return (Op == EBasicKeyOperation::Set) ? WeakObjPtr.IsValid() : !WeakObjPtr.IsValid();
}
