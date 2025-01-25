//--------------------
// kun 2025.01.23
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName)\
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName);\
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName);\
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName);\
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName);\

UCLASS(MinimalAPI, Blueprintable, Abstract)
class UBaseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
};
