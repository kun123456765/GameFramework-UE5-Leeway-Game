//--------------------
// kun 2024.12.22
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "BasePlayerState.generated.h"

class UGameAbilitySystemComponent;

UCLASS(MinimalAPI, Blueprintable, Abstract)
class ABasePlayerState : public APlayerState
	, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ABasePlayerState(const FObjectInitializer& ObjectInitializer);

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:
	void CreateAbilitySystemComponent(TObjectPtr<UGameAbilitySystemComponent>& Comp);

private:
	UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGameAbilitySystemComponent> ASC;
};
