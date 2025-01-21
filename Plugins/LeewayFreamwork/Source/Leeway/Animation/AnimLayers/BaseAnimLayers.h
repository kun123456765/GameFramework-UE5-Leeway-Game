//--------------------
//kun 2025.01.19
//--------------------

#pragma once

#include "Animation/AnimInstance.h"
#include "Leeway/Animation/AnimDataAsset/LocomotionAnimDataAsset.h"
#include "BaseAnimLayers.generated.h"

struct FAnimGraphContext;
struct FAnimLayersSet;
struct FLayerAnimSetBase;
//struct FAnimUpdateContext;
//struct FAnimNodeReference;

USTRUCT(BlueprintType)
struct FAnimLayersSettings
{
    GENERATED_USTRUCT_BODY()

    //动作切换的混合时间
    //会影响任何情况下的blending,暂时还不知道怎么控制只在"link layers"行为时才启用这个;
    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    float SetSequenceBlendingTime = 0.2f;

    //
    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FFloatInterval PlayRateMatchSpeedClamp = FFloatInterval(0.8f, 1.2f);
};

UCLASS(Blueprintable, MinimalAPI)
class UBaseAnimLayers : public UAnimInstance
{
    GENERATED_BODY()

public:
    UBaseAnimLayers();

public:
    virtual void NativeInitializeAnimation() override;
private:
    UFUNCTION(BlueprintCallable, meta = (AnimBlueprintFunction, BlueprintThreadSafe))
    void OnBecomeRelevant_IdleState(UPARAM(ref) FAnimUpdateContext& Context, UPARAM(ref) FAnimNodeReference& Node);
    UFUNCTION(BlueprintCallable, meta = (AnimBlueprintFunction, BlueprintThreadSafe))
    void OnUpdate_IdleState(UPARAM(ref) FAnimUpdateContext& Context, UPARAM(ref) FAnimNodeReference& Node);

    UFUNCTION(BlueprintCallable, meta = (AnimBlueprintFunction, BlueprintThreadSafe))
    void OnBecomeRelevant_CycleState(UPARAM(ref) FAnimUpdateContext& Context, UPARAM(ref) FAnimNodeReference& Node);
    UFUNCTION(BlueprintCallable, meta = (AnimBlueprintFunction, BlueprintThreadSafe))
    void OnUpdate_CycleState(UPARAM(ref) FAnimUpdateContext& Context, UPARAM(ref) FAnimNodeReference& Node);

    UFUNCTION(BlueprintCallable, meta = (AnimBlueprintFunction, BlueprintThreadSafe))
    void OnBecomeRelevant_StartState(UPARAM(ref) FAnimUpdateContext& Context, UPARAM(ref) FAnimNodeReference& Node);
    UFUNCTION(BlueprintCallable, meta = (AnimBlueprintFunction, BlueprintThreadSafe))
    void OnUpdate_StartState(UPARAM(ref) FAnimUpdateContext& Context, UPARAM(ref) FAnimNodeReference& Node);

    UFUNCTION(BlueprintCallable, meta = (AnimBlueprintFunction, BlueprintThreadSafe))
    void OnBecomeRelevant_StopState(UPARAM(ref) FAnimUpdateContext& Context, UPARAM(ref) FAnimNodeReference& Node);
    UFUNCTION(BlueprintCallable, meta = (AnimBlueprintFunction, BlueprintThreadSafe))
    void OnUpdate_StopState(UPARAM(ref) FAnimUpdateContext& Context, UPARAM(ref) FAnimNodeReference& Node);

private:
    void SetSequence(const FLayerAnimSetBase& AnimLayer, FAnimUpdateContext& Context, FAnimNodeReference& Node, bool UseMatchSpeed);
    
public:
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Leeway")
    FAnimLayersSettings AnimLayerSettings;
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Leeway")
    FAnimLayersSet AnimLayers;

private:
    TSharedPtr<FAnimGraphContext> AnimGraph;
    //TSharedPtr<FAnimLayersSet> AnimLayers;
};
