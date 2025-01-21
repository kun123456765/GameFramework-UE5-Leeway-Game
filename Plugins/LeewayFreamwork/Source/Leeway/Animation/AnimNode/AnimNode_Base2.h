//--------------------
//kun 2025.01.19
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimTypes.h"
#include "Animation/AnimNodeBase.h"
#include "Animation/AnimData/BoneMaskFilter.h"
#include "AnimNode_Base2.generated.h"

struct FInputBlendPose;

USTRUCT()
struct FAnimNode_Base2 : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

public:
	//~ FAnimNode_Base interface
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override { Super::Initialize_AnyThread(Context); }
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override { Super::CacheBones_AnyThread(Context); }
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override { Super::Update_AnyThread(Context); }
	virtual void Evaluate_AnyThread(FPoseContext& Output) override { Super::Evaluate_AnyThread(Output); }
	virtual void EvaluateComponentSpace_AnyThread(FComponentSpacePoseContext& Output) override { Super::EvaluateComponentSpace_AnyThread(Output); }
	virtual void GatherDebugData(FNodeDebugData& DebugData) override { Super::GatherDebugData(DebugData); }
	virtual int32 GetLODThreshold() const override { return Super::GetLODThreshold(); }
	virtual bool HasPreUpdate() const { return false; }
	virtual void PreUpdate(const UAnimInstance* InAnimInstance) {}
	virtual bool NeedsDynamicReset() const { return false; }
	virtual void ResetDynamics(ETeleportType InTeleportType) { Super::ResetDynamics(InTeleportType); }
	virtual void PostCompile(const class USkeleton* InSkeleton) {}
	virtual bool NeedsOnInitializeAnimInstance() const { return false; }
	//~ End of FAnimNode_Base interface
};
