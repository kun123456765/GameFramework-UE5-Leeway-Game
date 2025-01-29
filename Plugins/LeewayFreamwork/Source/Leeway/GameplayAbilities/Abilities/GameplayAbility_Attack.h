//--------------------
// kun 2025.01.23
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "Leeway/GameplayCommon/ActorTargeting/ActorTargetingOwnerInterface.h"
#include "GameplayAbility_Attack.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class UGameplayAbility_Attack : public UBaseGameplayAbility
{
	GENERATED_BODY()
};



//struct FTargetingShape
//{
//	FPrimitive
//};


UCLASS(MinimalAPI, Blueprintable)
class UGameplayAbility_Melee : public UBaseGameplayAbility
{
	GENERATED_BODY()

public:

protected:
	//void PerformTargeting();

};
