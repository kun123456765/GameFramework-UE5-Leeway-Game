//--------------------
// kun 2025.01.19
//--------------------


#include "BaseAnimLayers.h"

#include "AnimCharacterMovementLibrary.h"
#include "AnimDistanceMatchingLibrary.h"
#include "AnimExecutionContextLibrary.h"
#include "KismetAnimationLibrary.h"
#include "SequenceEvaluatorLibrary.h"
#include "SequencePlayerLibrary.h"
#include "Animation/AnimSequence.h"
#include "Animation/AnimInstanceProxy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Leeway/Animation/AnimDataAsset/LocomotionAnimDataAsset.h"
#include "Leeway/Animation/BaseAnimInstance.h"
#include "Leeway/Component/BaseCharacterMovementComponent.h"

UBaseAnimLayers::UBaseAnimLayers()
{

}

void UBaseAnimLayers::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    if (auto* SKMComp = GetOwningComponent())
    {
        if (auto* MainABP = Cast<UBaseAnimInstance>(SKMComp->GetAnimInstance()))
        {
            AnimGraph = MainABP->GetAnimGraphContext();
        }

        //if(auto* MoveComp = GetOwningActor()->FindComponentByClass<UBaseCharacterMovementComponent>())
        //{ 
        //	auto* DA_LocomotionAnim = MoveComp->DA_LocomotionAnim.Get();
        //	if (!DA_LocomotionAnim)
        //	{
        //		DA_LocomotionAnim = MoveComp->DA_LocomotionAnim.LoadSynchronous();
        //	}
        //	if (DA_LocomotionAnim)
        //	{
        //		auto& AnimSet = MoveComp->DA_LocomotionAnim.Get()->AnimSet;
        //		if (auto* AnimLayersSet = AnimSet.LayersSetMap.Find(MoveComp->GetAnimParams().CurrentAnimLayersTag))
        //		{
        //			AnimLayers = MakeShared<FAnimLayersSet>((*AnimLayersSet));
        //		}
        //	}
        //}

    }
}

void UBaseAnimLayers::OnBecomeRelevant_IdleState(FAnimUpdateContext& Context, FAnimNodeReference& Node)
{
    SetSequence(AnimLayers.IdleLayer, Context, Node, false);
}

void UBaseAnimLayers::OnUpdate_IdleState(UPARAM(ref) FAnimUpdateContext& Context, UPARAM(ref) FAnimNodeReference& Node)
{

}

void UBaseAnimLayers::OnBecomeRelevant_CycleState(UPARAM(ref)FAnimUpdateContext& Context, UPARAM(ref)FAnimNodeReference& Node)
{
    SetSequence(AnimLayers.CycleLayer, Context, Node, false);
}

void UBaseAnimLayers::OnUpdate_CycleState(UPARAM(ref)FAnimUpdateContext& Context, UPARAM(ref)FAnimNodeReference& Node)
{
}

void UBaseAnimLayers::OnBecomeRelevant_StartState(UPARAM(ref)FAnimUpdateContext& Context, UPARAM(ref)FAnimNodeReference& Node)
{
    SetSequence(AnimLayers.StartLayer, Context, Node, true);
}

void UBaseAnimLayers::OnUpdate_StartState(UPARAM(ref)FAnimUpdateContext& Context, UPARAM(ref)FAnimNodeReference& Node)
{
}

void UBaseAnimLayers::OnBecomeRelevant_StopState(UPARAM(ref)FAnimUpdateContext& Context, UPARAM(ref)FAnimNodeReference& Node)
{
    SetSequence(AnimLayers.StopLayer, Context, Node, true);
}

void UBaseAnimLayers::OnUpdate_StopState(UPARAM(ref)FAnimUpdateContext& Context, UPARAM(ref)FAnimNodeReference& Node)
{
}

void UBaseAnimLayers::SetSequence(const FLayerAnimSetBase& AnimLayer, FAnimUpdateContext& Context, FAnimNodeReference& Node, bool UseMatchSpeed)
{
    if (auto* AnimSequence = AnimLayer.StateAnim.Get())
    {
        EAnimNodeReferenceConversionResult Result = EAnimNodeReferenceConversionResult::Succeeded;
        FSequencePlayerReference SPRef = USequencePlayerLibrary::ConvertToSequencePlayer(Node, Result);
        
        //note by kun 2025.01.21
        //uncomment for directly cut;
        //USequencePlayerLibrary::SetSequence(SPRef, AnimSequence);

        USequencePlayerLibrary::SetSequenceWithInertialBlending(Context, SPRef, AnimSequence, AnimLayerSettings.SetSequenceBlendingTime);

        if(UseMatchSpeed)
        {
            if (AnimGraph.IsValid())
            {
                FVector2D PlayRateClamp(AnimLayerSettings.PlayRateMatchSpeedClamp.Min, AnimLayerSettings.PlayRateMatchSpeedClamp.Max);
                UAnimDistanceMatchingLibrary::SetPlayrateToMatchSpeed(SPRef, AnimGraph.Get()->Motion.DisplacementSpeed, PlayRateClamp);
            }
        }
    }
}
