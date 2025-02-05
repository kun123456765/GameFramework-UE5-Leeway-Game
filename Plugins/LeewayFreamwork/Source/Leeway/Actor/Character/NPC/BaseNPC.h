//--------------------
// kun 2024.12.22
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "Leeway/Actor/Character/BaseCharacter.h"
#include "BaseNPC.generated.h"

class UBaseAbilitySystemComponent;

UCLASS(MinimalAPI, Blueprintable)
class ABaseNPC : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ABaseNPC(const FObjectInitializer& ObjectInitializer);

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

private:

private:
	TObjectPtr<UBaseAbilitySystemComponent> AbilitySystemComponenct;
};
