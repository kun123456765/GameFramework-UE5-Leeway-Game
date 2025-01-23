//--------------------
// kun 2025.01.23
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "BaseAbilityTask.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class UBaseAbilityTask : public UAbilityTask
{
	GENERATED_BODY()

#if false
public:
	virtual bool IsWaitingOnAvatar() const override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
	virtual void BeginDestroy() override;
	virtual void InitSimulatedTask(UGameplayTasksComponent& InGameplayTasksComponent) override;
	virtual bool IsWaitingOnRemotePlayerdata() const override;
#endif
};
