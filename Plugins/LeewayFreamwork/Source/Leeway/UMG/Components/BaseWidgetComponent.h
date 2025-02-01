//--------------------
// kun 2025.01.31
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "BaseWidgetComponent.generated.h"


UCLASS(MinimalAPI, Blueprintable, ClassGroup = "UserInterface", hidecategories = (Object, Activation, "Components|Activation", Sockets, Base, Lighting, LOD, Mesh), editinlinenew, meta = (BlueprintSpawnableComponent))
class UBaseWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	virtual void InitWidget() override;
};
