//--------------------
// kun 2025.01.17
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Leeway/Animation/AnimDataAsset/LocomotionAnimDataAsset.h"
#include "BaseCharacterMovementComponent.generated.h"

class ULocomotionAnimDataAsset;

//ÓÉÂß¼­¿ØÖÆ;
USTRUCT(BlueprintType)
struct FAnimParams
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FGameplayTag CurrentAnimLayersTag;
};

UCLASS(MinimalAPI, Blueprintable)
class UBaseCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()
public:
    virtual void BeginPlay() override;

public:
    const FAnimParams& GetAnimParams() const { return AnimParams; }

public:
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Leeway")
    TSoftObjectPtr<ULocomotionAnimDataAsset> DA_LocomotionAnim;


    UFUNCTION()
    FAnimParams& ChangeAnimParams(UPARAM(ref) FAnimParams& InAnimParams)
    {
        AnimParams = InAnimParams;
    }

private:
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Leeway", meta = (AllowPrivateAccess = "true"))
    FAnimParams AnimParams;
};
