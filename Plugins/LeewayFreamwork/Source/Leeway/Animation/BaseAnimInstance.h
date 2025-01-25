//--------------------
//kun 2025.01.17
//--------------------

#pragma once

#include "Animation/AnimInstance.h"
//#include "Kismet/KismetMathLibrary.h"
//#include "AnimationStateMachineLibrary.h"
#include "BaseAnimInstance.generated.h"


USTRUCT(BlueprintType)
struct FAnimGraphContext_Initial
{
    GENERATED_USTRUCT_BODY()
};


USTRUCT(BlueprintType)
struct FAnimGraphContext_Common
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    float DeltaTime = 0.f;
};

USTRUCT(BlueprintType)
struct FAnimGraphContext_Motion
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    float Displacement = 0.f;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    float DisplacementSpeed = 0.f;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    float LastYaw = 0.f;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    float YawOffset = 0.f;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    float YawSpeed = 0.f;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FVector Velocity;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FVector Acceleration;
};

USTRUCT(BlueprintType)
struct FAnimGraphContext
{
    GENERATED_USTRUCT_BODY()


    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FAnimGraphContext_Initial Initial;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FAnimGraphContext_Common Common;

    UPROPERTY(BlueprintReadWrite, EditAnyWhere)
    FAnimGraphContext_Motion Motion;
};

UCLASS(MinimalAPI, Blueprintable, Abstract)
class UBaseAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

public:
    UBaseAnimInstance();

public:
    //~ Begin UObject Interface
    //virtual void Serialize(FArchive& Ar) override { Super::Serialize(FArchive & Ar); }
    //virtual void BeginDestroy() override { Super::BeginDestroy(); }
    //virtual void PostInitProperties() override { Super::PostInitProperties(); }
    //virtual UWorld* GetWorld() const override { return Super::GetWorld(); }
    //~ End UObject Interface

public:
    //~ Begin UAnimInstance Interface

    // 给子类干活的一组时机;
    virtual void NativeInitializeAnimation() {}
    virtual void NativeUpdateAnimation(float DeltaSeconds);
    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) {}
    virtual void NativePostEvaluateAnimation() {}
    virtual void NativeUninitializeAnimation() {}
    virtual void NativeBeginPlay() {}

    // Super只处理SKMeshComp的关系，我倒是也想不出来特例情景是什么;
    //virtual APawn* TryGetPawnOwner() const { return Super::TryGetPawnOwner(); }

    // pose就是一个 Map<BoneName, Transform>;
    // 保存pose按说应该直接返回一个数据结构（事实上给蓝图用的确实返了）
    // save/add/remove/get 四种基本操作;
    // 目前想不明白为什么需要在save的时候做个virtual口子;
    //virtual void SavePoseSnapshot(FName SnapshotName) { Super::SavePoseSnapshot(SnapshotName); }
    //virtual void SnapshotPose(UPARAM(ref) FPoseSnapshot& Snapshot) { Super::SnapshotPose(Snapshot); }

    // 全项目只有 AnimPrivewInstance 关上了(false);
    //virtual bool CanRunParallelWork() const { return true; }

    // 看名字就很重要; 
    // ref传参是为了处理MontageSync相关的事情;
    //virtual void OnMontageInstanceStopped(FAnimMontageInstance& StoppedMontageInstance) { Super::OnMontageInstanceStopped(StoppedMontageInstance); }

    // AnimLayer 是一个很重要的组织形式，在ue5以后，可以动态启用其他ABP的AnimLayers，这需要提前建立一个新的 AnimLayerInterface(ALI)，并且主ABP和子ABP都需要添加接口实现。
    // 然后就可以将原本AnimGraph里的东西挪到子ABP中。美中不足的是只能通过MainABP拿参数。
    // 与LinkedAnimGraph的区别：
    // 1、
    // 2、
    //virtual void LinkAnimClassLayers(TSubclassOf<UAnimInstance> InClass);
    //virtual void UnlinkAnimClassLayers(TSubclassOf<UAnimInstance> InClass);

    // 更新Montage,主要是处理blendingweight和notifies;
    //virtual void Montage_UpdateWeight(float DeltaSeconds);
    //virtual void Montage_Advance(float DeltaSeconds);

    //FastPath相关的提示?这个应该开啊，方便查错;
    //virtual bool PCV_ShouldWarnAboutNodesNotUsingFastPath() const { return false; }
    //virtual bool PCV_ShouldNotifyAboutNodesNotUsingFastPath() const { return false; }

    //// 便捷工具
    //virtual void ApplyAnimOverridesToCDO(FCompilerResultsLog& MessageLog) {}

    // URO优化相关;
    //virtual void OnUROSkipTickAnimation() {}
    //virtual void OnUROPreInterpolation_AnyThread(FAnimationEvaluationContext& InOutContext) {}

    // LinkedInstances更新时机相关;
    //virtual void PreUpdateLinkedInstances(float DeltaSeconds) {}

    // Debug相关;
    //virtual void DisplayDebugInstance(FDisplayDebugManager& DisplayDebugManager, float& Indent) { Super::DisplayDebugInstance(DisplayDebugManager, Indent); }

    // LOD 
    //virtual int32 GetLODLevel() const { return Super::GetLODLevel(); }

    // 工具控制相关;
    //virtual bool ShouldTriggerAnimNotifyState(const UAnimNotifyState* AnimNotifyState) const { return Super::ShouldTriggerAnimNotifyState(AnimNotifyState); }

#if WITH_EDITOR
    //virtual void HandleObjectsReinstanced(const TMap<UObject*, UObject*>& OldToNewInstanceMap) { return Super::HandleObjectsReinstanced(const TMap<UObject*, UObject*>& OldToNewInstanceMap); }
#endif
    //~ End UAnimInstance Interface

protected:
    //~ Begin UAnimInstance Interface

    // Notify相关;
    //virtual bool HandleNotify(const FAnimNotifyEvent& AnimNotifyEvent) { return Super::HandleNotify(AnimNotifyEvent); }

    // Update相关;
    //virtual void PreUpdateAnimation(float DeltaSeconds){ Super::PreUpdateAnimation(DeltaSeconds); }

    // AnimInstanceProxy 相关;
    //virtual FAnimInstanceProxy* CreateAnimInstanceProxy() { return Super::CreateAnimInstanceProxy(); }
    //virtual void DestroyAnimInstanceProxy(FAnimInstanceProxy* InProxy) { return Super::DestroyAnimInstanceProxy(InProxy); }
    //~ End UAnimInstance Interface


public:
    const TSharedRef<FAnimGraphContext> GetAnimGraphContext() const;

private:
    void UpdateAnimGraphContext(float DeltaSeconds);

private:
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Leeway", meta = (AllowPrivateAccess = "true"))
    FAnimGraphContext AnimGraphContext;
};
