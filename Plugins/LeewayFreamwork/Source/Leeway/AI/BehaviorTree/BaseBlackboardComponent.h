//--------------------
// kun 2025.02.06
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseBlackboardComponent.generated.h"

class ABaseCharacter;

UCLASS(ClassGroup = AI, meta = (BlueprintSpawnableComponent), hidecategories = (Sockets, Collision), MinimalAPI)
class UBaseBlackboardComponent : public UBlackboardComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Leeway|AI|Components|Blackboard")
	class ABaseCharacter* GetValueAsBaseCharacter(const FName& KeyName) const;

	UFUNCTION(BlueprintCallable, Category = "Leeway|AI|Components|Blackboard")
	void SetValueAsBaseCharacter(const FName& KeyName, ABaseCharacter* ObjectValue);
};
