//--------------------
// kun 2025.01.31
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Leeway/UMG/Components/BaseWidgetComponent.h"
#include "BaseUserWidget.generated.h"

class UBaseWidgetComponent;

UCLASS(MinimalAPI, Blueprintable, Abstract)
class UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = UserInterface)
	virtual void SetOwningComponent(UBaseWidgetComponent* WidgetComponent);
	
	UFUNCTION(BlueprintCallable, Category = UserInterface)
	virtual UBaseWidgetComponent* GetOwningComponent() { return BaseWidgetComponent.Get(); }

private:
	TWeakObjectPtr<UBaseWidgetComponent> BaseWidgetComponent;
};
