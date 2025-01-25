//--------------------
// kun 2025.01.23
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BaseAttributeSet.h"
#include "LocomotionAttributeSet.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class ULocomotionAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:
	ATTRIBUTE_ACCESSORS(ULocomotionAttributeSet, MaxSpeed);
	ATTRIBUTE_ACCESSORS(ULocomotionAttributeSet, MaxAcceleration);
	ATTRIBUTE_ACCESSORS(ULocomotionAttributeSet, AccelerationMultiper);

private:
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxSpeed;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxAcceleration;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData AccelerationMultiper;
};
