//--------------------
// kun 2025.02.06
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

class UBaseBehaviorTreeComponent;
class UBaseBlackboardComponent;

UCLASS(ClassGroup = AI, BlueprintType, Blueprintable, MinimalAPI)
class ABaseAIController : public AAIController
{
    GENERATED_BODY()

public:
    ABaseAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

#if false
    virtual FString GetDebugIcon() const;

    /// �����Ǽ���PathFollowing����Ĵ�����,�൱��PathFollowingHandle�Ľ�ɫ;
    virtual FPathFollowingRequestResult MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath = nullptr);
    virtual FAIRequestID RequestMove(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr Path);
    virtual void FindPathForMoveRequest(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query, FNavPathSharedPtr& OutPath) const;
    virtual bool PreparePathfinding(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query);
    virtual FAIRequestID RequestPathAndMove(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query);
    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);
    virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

    /// ��Ϊ�����;
    virtual bool RunBehaviorTree(UBehaviorTree* BTAsset);
    virtual void CleanupBrainComponent();
    virtual bool ShouldSyncBlackboardWith(const UBlackboardComponent& OtherBlackboardComponent) const;
    virtual bool InitializeBlackboard(UBlackboardComponent& BlackboardComp, UBlackboardData& BlackboardAsset);

    /*
    * ��֪ϵͳҲ�ǱȽ��Ե�ϵͳ����GameplayTargetingSystem�ǲ����ص���?
    */
    virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

    /// FocusInformation �Ĳ����ӿ�;
    /*
    * note by kun 2025.02.06
    * ����Ϊ����һ�������ª�Ŀ���Ϊ��������Ϣ��ȡ����;
    */
    virtual FVector GetFocalPointOnActor(const AActor* Actor) const;
    virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true);
    virtual void SetFocalPoint(FVector NewFocus, EAIFocusPriority::Type InPriority = EAIFocusPriority::Gameplay);
    virtual void SetFocus(AActor* NewFocus, EAIFocusPriority::Type InPriority = EAIFocusPriority::Gameplay);
    virtual void ClearFocus(EAIFocusPriority::Type InPriority);

    // GameplayTask�����������ȼ���صĽӿ�;
    virtual uint8 GetGameplayTaskDefaultPriority() const {
        return FGameplayTasks::DefaultPriority - 1;
        virtual void OnGameplayTaskResourcesClaimed(FGameplayResourceSet NewlyClaimed, FGameplayResourceSet FreshlyReleased);
#endif

protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI)
    TObjectPtr<UBaseBehaviorTreeComponent> LWBehaviroTree;
    UPROPERTY(BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UBaseBlackboardComponent> LWBlackboard;
};
