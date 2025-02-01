//--------------------
// kun 2025.01.31
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BaseUserWidget.h"
#include "LWCharacterUserWidget.generated.h"

class UBaseWidgetComponent;
class ABaseCharacter;

UCLASS(MinimalAPI, Blueprintable)
class ULWCharacterUserWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetOwningComponent(UBaseWidgetComponent* WidgetComponent) override;

	UFUNCTION(BlueprintCallable, Category = UserInterface)
	ABaseCharacter* GetBaseCharacter() const { return BaseCharacter.Get(); }

private:
	TWeakObjectPtr<ABaseCharacter> BaseCharacter;
};
