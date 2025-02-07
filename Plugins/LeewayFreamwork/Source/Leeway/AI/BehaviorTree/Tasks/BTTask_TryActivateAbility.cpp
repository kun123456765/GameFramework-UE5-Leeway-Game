//--------------------
// kun 2025.02.06
//--------------------

#include "BTTask_TryActivateAbility.h"
#include "Leeway/AI/BehaviorTree/BaseBlackboardComponent.h"
#include "Leeway/AI/BehaviorTree/Blackboard/BlackboardKeyType_GameplayTag.h"
#include "Leeway/AI/BaseAIController.h"
#include "Leeway/Actor/Character/BaseCharacter.h"
#include "UObject/Class.h"

#include "Leeway/GameplayAbilities/BaseAbilitySystemComponent.h"

UBTTask_TryActivateAbility::UBTTask_TryActivateAbility(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
	NodeName = "TryActivateAbility";
	//这句话很有意思，利用了重载函数地址不一致的特性去初始化变量;
	INIT_TASK_NODE_NOTIFY_FLAGS();

	// todo kun 2025.02.07
	// 可以继承BlackboardKeySelector，添加 Add GameplayTag Filter, 或者其他规则;
	//BlackboardKey.AddClassFilter(this, GET_MEMBER_NAME_CHECKED(UBTTask_TryActivateAbility, BlackboardKey), FGameplayTag::StaticStruct()->GetClass());
}

uint16 UBTTask_TryActivateAbility::GetInstanceMemorySize() const
{
	return sizeof(FInstanceMemory);
}

void UBTTask_TryActivateAbility::InitializeMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryInit::Type InitType) const
{
	InitializeNodeMemory<FInstanceMemory>(NodeMemory, InitType);
}

void UBTTask_TryActivateAbility::CleanupMemory(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTMemoryClear::Type CleanupType) const
{
	CleanupNodeMemory<FInstanceMemory>(NodeMemory, CleanupType);
}

EBTNodeResult::Type UBTTask_TryActivateAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	FInstanceMemory* MyMemory = CastInstanceNodeMemory<FInstanceMemory>(NodeMemory);
	AAIController* MyController = OwnerComp.GetAIOwner();
	if (MyController == nullptr)
	{
		UE_VLOG(OwnerComp.GetOwner(), LogBehaviorTree, Error, TEXT("UBTTask_MoveTo::ExecuteTask failed since AIController is missing."));
		NodeResult = EBTNodeResult::Failed;
	}
	else
	{
		NodeResult = DoExecuteTask(OwnerComp, NodeMemory);
	}

	if (NodeResult != EBTNodeResult::Failed)
	{
		// 监听BB变化;
		UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
		if (ensure(BlackboardComp))
		{
			if (MyMemory->BBObserverDelegateHandle.IsValid())
			{
				UE_VLOG(MyController, LogBehaviorTree, Warning, TEXT("%s::ExecuteTask \'%s\' Old BBObserverDelegateHandle is still valid! Removing old Observer."), *GetNameSafe(GetClass()), *GetNodeName());
				BlackboardComp->UnregisterObserver(BlackboardKey.GetSelectedKeyID(), MyMemory->BBObserverDelegateHandle);
			}
			MyMemory->BBObserverDelegateHandle = BlackboardComp->RegisterObserver(BlackboardKey.GetSelectedKeyID(), this, FOnBlackboardChangeNotification::CreateUObject(this, &ThisClass::HandleOnBlackboardValueChange));
		}
	}

	return NodeResult;
}

void UBTTask_TryActivateAbility::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
}

void UBTTask_TryActivateAbility::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	if (auto* ASC = GetASC(OwnerComp, NodeMemory))
	{
		FInstanceMemory* MyMemory = CastInstanceNodeMemory<FInstanceMemory>(NodeMemory);
		ASC->OnAbilityEnded.Remove(MyMemory->AbilityEndedHandle);
	}
}

EBlackboardNotificationResult UBTTask_TryActivateAbility::HandleOnBlackboardValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID)
{
	UBehaviorTreeComponent* BehaviorComp = Cast<UBehaviorTreeComponent>(Blackboard.GetBrainComponent());
	if (BehaviorComp == nullptr)
	{
		return EBlackboardNotificationResult::RemoveObserver;
	}

	EBlackboardNotificationResult Result = OnBlackboardValueChange(Blackboard, ChangedKeyID);
	if (Result == EBlackboardNotificationResult::RemoveObserver)
	{
		uint8* RawMemory = BehaviorComp->GetNodeMemory(this, BehaviorComp->FindInstanceContainingNode(this));
		FInstanceMemory* MyMemory = CastInstanceNodeMemory<FInstanceMemory>(RawMemory);
		MyMemory->BBObserverDelegateHandle.Reset(); //-V595
	}
	return Result;
}

EBlackboardNotificationResult UBTTask_TryActivateAbility::OnBlackboardValueChange(const UBlackboardComponent& Blackboard, FBlackboard::FKey ChangedKeyID)
{
	return EBlackboardNotificationResult::ContinueObserving;
}

EBTNodeResult::Type UBTTask_TryActivateAbility::DoExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FGameplayTag TriggerTag = GetTriggerTag(OwnerComp, NodeMemory);
	if (TriggerTag.IsValid())
	{
		if (auto* ASC = GetASC(OwnerComp, NodeMemory))
		{
			FInstanceMemory* MyMemory = CastInstanceNodeMemory<FInstanceMemory>(NodeMemory);
			//ASC->AbilityActivatedCallbacks.AddUObject(this, &ThisClass::OnAbilityActivate);
			//if (ASC->TryActivateAbilityByClass(AbilityClass))
			//{
			//	auto* AbilitySpec = ASC->FindAbilitySpecFromClass(AbilityClass);
			//	AbilitySpec->Handle;
			//}

            //FTriggerAbilityFromGameplayEventDelegate Delegate;
            //Delegate.BindUObject(this, &UBTTask_TryActivateAbility::OnCallback, OwnerComp, NodeMemory);
            TWeakObjectPtr<UBehaviorTreeComponent> OwnerCompPtr = &OwnerComp;
            FTriggerAbilityCallbackScope Scope(ASC);
            Scope.TriggerAbilityCallback.BindWeakLambda(this, [this, OwnerCompPtr, NodeMemory](const TArray<FGameplayAbilitySpecHandle>& ActivatedHandles)
                {
                    OnCallback(ActivatedHandles, OwnerCompPtr, NodeMemory);
                });
            MyMemory->AbilityEndedHandle = ASC->OnAbilityEnded.AddWeakLambda(this, [this, OwnerCompPtr, NodeMemory](const FAbilityEndedData& EndedData)
                {
                    OnAbilityEnded(EndedData, OwnerCompPtr, NodeMemory);
                });
            FGameplayEventData Payload;
            ASC->HandleGameplayEvent(TriggerTag, &Payload);
        }
    }

	return EBTNodeResult::Type::InProgress;
}

void UBTTask_TryActivateAbility::DoTickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (auto* ASC = GetASC(OwnerComp, NodeMemory))
	{
		FInstanceMemory* MyMemory = CastInstanceNodeMemory<FInstanceMemory>(NodeMemory);
		if (auto* AblitySpec = ASC->FindAbilitySpecFromHandle(MyMemory->AbilitySpecHandle))
		{
			if (!AblitySpec->IsActive())
			{
				//FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
	}
}

FGameplayTag UBTTask_TryActivateAbility::GetTriggerTag(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	FGameplayTag TriggerTag;
	if (ensure(OwnerComp.GetAIOwner()))
	{
		if (UBaseBlackboardComponent* Blackboard = Cast<UBaseBlackboardComponent>(OwnerComp.GetAIOwner()->GetBlackboardComponent()))
		{
			TriggerTag = Blackboard->GetValueRef<UBlackboardKeyType_GameplayTag>(BlackboardKey.GetSelectedKeyID());
			if (!TriggerTag.IsValid())
			{
				TriggerTag = TriggerTag_PerTaskNode;
			}
		}
	}

	return TriggerTag;
}

UBaseAbilitySystemComponent* UBTTask_TryActivateAbility::GetASC(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (ensure(OwnerComp.GetAIOwner()))
	{
		if (auto* BaseAIController = Cast<ABaseAIController>(OwnerComp.GetAIOwner()))
		{
			if (auto* BaseCharacter = BaseAIController->GetPawn<ABaseCharacter>())
			{
				auto* ASC = Cast<UBaseAbilitySystemComponent>(BaseCharacter->GetAbilitySystemComponent());
				return ASC;
			}
		}
	}
	return nullptr;
}

void UBTTask_TryActivateAbility::OnAbilityActivate(UGameplayAbility* ActivatedAbility, TWeakObjectPtr<UBehaviorTreeComponent> OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.IsValid())
	{
		return;
	}

	FGameplayTag TriggerTag = GetTriggerTag(*OwnerComp.Get(), NodeMemory);
	if (TriggerTag.IsValid())
	{
		if (ActivatedAbility->AbilityTags.HasTag(TriggerTag))
		{
			//todo
		}
	}
}

void UBTTask_TryActivateAbility::OnAbilityEnded(const FAbilityEndedData& EndedData, TWeakObjectPtr<UBehaviorTreeComponent> OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.IsValid())
	{
		return;
	}

	FInstanceMemory* MyMemory = CastInstanceNodeMemory<FInstanceMemory>(NodeMemory);

	if (EndedData.AbilitySpecHandle == MyMemory->AbilitySpecHandle)
	{
		if (EndedData.bWasCancelled)
		{
			FinishLatentTask(*OwnerComp.Get(), EBTNodeResult::Failed);
			//FinishLatentAbort(*OwnerComp.Get());
		}
		else
		{
			FinishLatentTask(*OwnerComp.Get(), EBTNodeResult::Succeeded);
		}
	}
}

void UBTTask_TryActivateAbility::OnCallback(const TArray<FGameplayAbilitySpecHandle>& ActivatedHandles, TWeakObjectPtr<UBehaviorTreeComponent> OwnerComp, uint8* NodeMemory)
{
	if (!OwnerComp.IsValid())
	{
		return;
	}

	FInstanceMemory* MyMemory = CastInstanceNodeMemory<FInstanceMemory>((uint8*)NodeMemory);
	if (ActivatedHandles.Num())
	{
		MyMemory->AbilitySpecHandle = ActivatedHandles[0];
	}
}
