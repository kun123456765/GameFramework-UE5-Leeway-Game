//--------------------
// kun 2025.02.06
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameplayAbilitySpecHandle.h"
#include "BTTask_TryActivateAbility.generated.h"

class ABaseAIController;
class ABaseCharacterActor;
class UBaseAbilitySystemComponent;
class UGameplayAbility;
struct FAbilityEndedData;

struct FBTTaskInstanceMemory_TryActivateAbility
{
    TObjectPtr<ABaseAIController> AIOwner;
    FDelegateHandle BBObserverDelegateHandle;
    FGameplayAbilitySpecHandle AbilitySpecHandle;
    FDelegateHandle AbilityEndedHandle;
};

UCLASS(MinimalAPI, Blueprintable)
class UBTTask_TryActivateAbility : public UBTTask_BlackboardBase
{
    GENERATED_BODY()

    typedef FBTTaskInstanceMemory_TryActivateAbility FInstanceMemory;

public:
    UBTTask_TryActivateAbility(const FObjectInitializer& ObjectInitializer);

    virtual uint16 GetInstanceMemorySize() const override;
    virtual void InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const override;
    virtual void CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const override;

public:
    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

protected:
    EBlackboardNotificationResult HandleOnBlackboardValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);

protected:
    virtual EBlackboardNotificationResult OnBlackboardValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID);
    virtual EBTNodeResult::Type DoExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
    virtual void DoTickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds);

protected:
    FGameplayTag GetTriggerTag(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
    UBaseAbilitySystemComponent* GetASC(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
    void OnAbilityActivate(UGameplayAbility* ActivatedAbility, TWeakObjectPtr<UBehaviorTreeComponent> OwnerComp, uint8* NodeMemory);
	//UFUNCTION()
	void OnAbilityEnded(const FAbilityEndedData& EndedData, TWeakObjectPtr<UBehaviorTreeComponent> OwnerComp, uint8* NodeMemory);
    void OnCallback(const TArray<FGameplayAbilitySpecHandle>& ActivatedHandles, TWeakObjectPtr<UBehaviorTreeComponent> OwnerComp, uint8* NodeMemory);

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Leeway)
    FGameplayTag TriggerTag_PerTaskNode;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Leeway)
    TSubclassOf<UGameplayAbility> AbilityClass;
};
