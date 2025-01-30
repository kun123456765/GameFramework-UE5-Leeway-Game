//--------------------
// kun 2025.01.17
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "LocomotionAnimDataAsset.generated.h"

class UAnimSequence;

USTRUCT(BlueprintType)
struct FSoftObjectPtr2
{
    GENERATED_USTRUCT_BODY()

public:
    template<class T = UObject>
    T* Get() const
    {
        if (!ObjectPtr.IsNull())
        {
            if (ObjectPtr.IsPending() || !ObjectPtr.IsValid())
            {
                T* LoadedObject = Cast<T>(ObjectPtr.LoadSynchronous());
                return LoadedObject;
            }
        }
        return nullptr;
    }

private:
    FSoftObjectPtr ObjectPtr;
};


USTRUCT(BlueprintType)
struct FIdleBreakSettings
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    TArray<TObjectPtr<UAnimSequence>> IdleBreakAnims;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FFloatInterval RandomInterval = FFloatInterval(3, 5);
};

USTRUCT(BlueprintType)
struct FLayerAnimSetBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    TObjectPtr<UAnimSequence> StateAnim;
};

USTRUCT(BlueprintType)
struct FIdleLayerAnimSet : public FLayerAnimSetBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FIdleBreakSettings IdleBreak;
};

USTRUCT(BlueprintType)
struct FCycleLayerAnimSet : public FLayerAnimSetBase
{
    GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType)
struct FStartLayerAnimSet : public FLayerAnimSetBase
{
    GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType)
struct FStopAnimLayerAnimSet : public FLayerAnimSetBase
{
    GENERATED_USTRUCT_BODY()
};

USTRUCT(BlueprintType)
struct FAnimLayersSet
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FIdleLayerAnimSet IdleLayer;
    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FCycleLayerAnimSet CycleLayer;
    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FStartLayerAnimSet StartLayer;
    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FStopAnimLayerAnimSet StopLayer;
};

USTRUCT(BlueprintType)
struct FStandStanceAnimLayersSet
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FAnimLayersSet Unarmed;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FAnimLayersSet Melee;
};

USTRUCT(BlueprintType)
struct FStanceSet
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FStandStanceAnimLayersSet Stand;
};

USTRUCT(BlueprintType)
struct FLWAnimSet
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FStanceSet Stance;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    TMap<FGameplayTag, FAnimLayersSet> LayersSetMap;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    TMap<FGameplayTag, TSubclassOf<class UBaseAnimLayers>> AnimLayersClasses;
};

UCLASS(BlueprintType)
class ULocomotionAnimDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FLWAnimSet AnimSet;
};
