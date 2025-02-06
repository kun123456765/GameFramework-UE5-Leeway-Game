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

    /// 以下是集成PathFollowing所需的处理函数,相当于PathFollowingHandle的角色;
    virtual FPathFollowingRequestResult MoveTo(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr* OutPath = nullptr);
    virtual FAIRequestID RequestMove(const FAIMoveRequest& MoveRequest, FNavPathSharedPtr Path);
    virtual void FindPathForMoveRequest(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query, FNavPathSharedPtr& OutPath) const;
    virtual bool PreparePathfinding(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query);
    virtual FAIRequestID RequestPathAndMove(const FAIMoveRequest& MoveRequest, FPathFindingQuery& Query);
    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);
    virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

    /// 行为树相关;
    virtual bool RunBehaviorTree(UBehaviorTree* BTAsset);
    virtual void CleanupBrainComponent();
    virtual bool ShouldSyncBlackboardWith(const UBlackboardComponent& OtherBlackboardComponent) const;
    virtual bool InitializeBlackboard(UBlackboardComponent& BlackboardComp, UBlackboardData& BlackboardAsset);

    /*
    * 感知系统也是比较迷的系统，和GameplayTargetingSystem是不是重叠了?
    */
    virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

    /// FocusInformation 的操作接口;
    /*
    * note by kun 2025.02.06
    * 我认为这是一个极其简陋的跨行为上下文信息存取方案;
    */
    virtual FVector GetFocalPointOnActor(const AActor* Actor) const;
    virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true);
    virtual void SetFocalPoint(FVector NewFocus, EAIFocusPriority::Type InPriority = EAIFocusPriority::Gameplay);
    virtual void SetFocus(AActor* NewFocus, EAIFocusPriority::Type InPriority = EAIFocusPriority::Gameplay);
    virtual void ClearFocus(EAIFocusPriority::Type InPriority);

    // GameplayTask调度任务优先级相关的接口;
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
