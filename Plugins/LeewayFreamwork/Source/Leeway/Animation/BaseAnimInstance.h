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

    // ������ɻ��һ��ʱ��;
    virtual void NativeInitializeAnimation() {}
    virtual void NativeUpdateAnimation(float DeltaSeconds);
    virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) {}
    virtual void NativePostEvaluateAnimation() {}
    virtual void NativeUninitializeAnimation() {}
    virtual void NativeBeginPlay() {}

    // Superֻ����SKMeshComp�Ĺ�ϵ���ҵ���Ҳ�벻���������龰��ʲô;
    //virtual APawn* TryGetPawnOwner() const { return Super::TryGetPawnOwner(); }

    // pose����һ�� Map<BoneName, Transform>;
    // ����pose��˵Ӧ��ֱ�ӷ���һ�����ݽṹ����ʵ�ϸ���ͼ�õ�ȷʵ���ˣ�
    // save/add/remove/get ���ֻ�������;
    // Ŀǰ�벻����Ϊʲô��Ҫ��save��ʱ������virtual����;
    //virtual void SavePoseSnapshot(FName SnapshotName) { Super::SavePoseSnapshot(SnapshotName); }
    //virtual void SnapshotPose(UPARAM(ref) FPoseSnapshot& Snapshot) { Super::SnapshotPose(Snapshot); }

    // ȫ��Ŀֻ�� AnimPrivewInstance ������(false);
    //virtual bool CanRunParallelWork() const { return true; }

    // �����־ͺ���Ҫ; 
    // ref������Ϊ�˴���MontageSync��ص�����;
    //virtual void OnMontageInstanceStopped(FAnimMontageInstance& StoppedMontageInstance) { Super::OnMontageInstanceStopped(StoppedMontageInstance); }

    // AnimLayer ��һ������Ҫ����֯��ʽ����ue5�Ժ󣬿��Զ�̬��������ABP��AnimLayers������Ҫ��ǰ����һ���µ� AnimLayerInterface(ALI)��������ABP����ABP����Ҫ��ӽӿ�ʵ�֡�
    // Ȼ��Ϳ��Խ�ԭ��AnimGraph��Ķ���Ų����ABP�С����в������ֻ��ͨ��MainABP�ò�����
    // ��LinkedAnimGraph������
    // 1��
    // 2��
    //virtual void LinkAnimClassLayers(TSubclassOf<UAnimInstance> InClass);
    //virtual void UnlinkAnimClassLayers(TSubclassOf<UAnimInstance> InClass);

    // ����Montage,��Ҫ�Ǵ���blendingweight��notifies;
    //virtual void Montage_UpdateWeight(float DeltaSeconds);
    //virtual void Montage_Advance(float DeltaSeconds);

    //FastPath��ص���ʾ?���Ӧ�ÿ�����������;
    //virtual bool PCV_ShouldWarnAboutNodesNotUsingFastPath() const { return false; }
    //virtual bool PCV_ShouldNotifyAboutNodesNotUsingFastPath() const { return false; }

    //// ��ݹ���
    //virtual void ApplyAnimOverridesToCDO(FCompilerResultsLog& MessageLog) {}

    // URO�Ż����;
    //virtual void OnUROSkipTickAnimation() {}
    //virtual void OnUROPreInterpolation_AnyThread(FAnimationEvaluationContext& InOutContext) {}

    // LinkedInstances����ʱ�����;
    //virtual void PreUpdateLinkedInstances(float DeltaSeconds) {}

    // Debug���;
    //virtual void DisplayDebugInstance(FDisplayDebugManager& DisplayDebugManager, float& Indent) { Super::DisplayDebugInstance(DisplayDebugManager, Indent); }

    // LOD 
    //virtual int32 GetLODLevel() const { return Super::GetLODLevel(); }

    // ���߿������;
    //virtual bool ShouldTriggerAnimNotifyState(const UAnimNotifyState* AnimNotifyState) const { return Super::ShouldTriggerAnimNotifyState(AnimNotifyState); }

#if WITH_EDITOR
    //virtual void HandleObjectsReinstanced(const TMap<UObject*, UObject*>& OldToNewInstanceMap) { return Super::HandleObjectsReinstanced(const TMap<UObject*, UObject*>& OldToNewInstanceMap); }
#endif
    //~ End UAnimInstance Interface

protected:
    //~ Begin UAnimInstance Interface

    // Notify���;
    //virtual bool HandleNotify(const FAnimNotifyEvent& AnimNotifyEvent) { return Super::HandleNotify(AnimNotifyEvent); }

    // Update���;
    //virtual void PreUpdateAnimation(float DeltaSeconds){ Super::PreUpdateAnimation(DeltaSeconds); }

    // AnimInstanceProxy ���;
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
