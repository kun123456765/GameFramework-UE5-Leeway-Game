//--------------------
// kun 2025.01.27
//--------------------

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "ActorTargetingBlueprintLibrary.generated.h"

struct FActorTargetingContextSharedPtr;
struct FActorTargetingContext;

USTRUCT(BlueprintType)
struct FActorTargetingContextSharedPtr
{
    GENERATED_USTRUCT_BODY()

    TSharedPtr<FActorTargetingContext> Context;
};

UCLASS()
class LEEWAY_API UActorTargetingBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, CustomThunk, meta = (CustomStructureParam = "Context"))
    static void CreateActorTargetingContext(FActorTargetingContextSharedPtr& ContextHandle, const FActorTargetingContext& Context);
    DECLARE_FUNCTION(execCreateActorTargetingContext);
};
