//--------------------
// kun 2025.02.06
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "LWBTFunctionLibrary.generated.h"

class ABaseCharacter;

UCLASS(meta = (RestrictedToClasses = "BTNode"), MinimalAPI)
class ULWBTFunctionLibrary : public UBTFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "LW|AI|BehaviorTree", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
	static ABaseCharacter* GetBlackboardValueAsBaseCharacter(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);
};
