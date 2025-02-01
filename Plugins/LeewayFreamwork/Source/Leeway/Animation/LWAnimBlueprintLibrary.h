//--------------------
// kun 2025.01.31
//--------------------

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "LWAnimBlueprintLibrary.generated.h"

class UAnimMontage;
struct FAnimMetaData_HitReaction;
class ACharacter;
struct FTargetingResult_Overlap;

UCLASS()
class LEEWAY_API ULWAnimBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    static FName ChooseFittestMontageSectionForHitReaction(const UAnimMontage* MontageToPlay, const FAnimMetaData_HitReaction& AnimMetaData);
    UFUNCTION(BlueprintCallable)
    static FName ChooseFittestMontageSectionForHitReactionWithActor(const UAnimMontage* MontageToPlay, const ACharacter* TargetActor, const ACharacter* SourceActor, const FTargetingResult_Overlap& OverlapResult);
};
