//--------------------
// kun 2025.01.23
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BaseAttributeSet.h"
#include "CombatAttributeSet.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class UCombatAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

private:
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Shield);
};
