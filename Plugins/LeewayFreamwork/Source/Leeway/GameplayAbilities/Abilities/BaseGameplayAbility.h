//--------------------
// kun 2025.01.23
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemComponent.h"
#include "BaseGameplayAbility.generated.h"

/*
// note by kun 2025.01.23
Runtime handle progress:

OnGiveAbility
	InternalTryActivateAbility
	ShouldAbilityRespondToEvent
	CanActivateAbility
		ShouldActivateAbility(ENetRole)
		DoesAbilitySatisfyTagRequirements(Tags)
	PreActivate
		SetCurrentActorInfo
			OnAvatarSet
		SetCurrentActivationInfo
	ActivateAbility
		CommitAbility
			CommitCheck
				CheckCooldown
				CheckCost
			CommitExecute
				ApplyCooldown
				ApplyCost
		ConfirmActivateSucceed(RPC_S2C)
			PostNetInit
	EndAbility
	CancelAbility
OnRemoveAbility
*/
UCLASS(MinimalAPI, Blueprintable, Abstract)
class UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

	// note by kun 2025.01.23
	// 按需继承,忘了细节就回来查;
#if false
public:
	//~Begin UObject
	virtual UWorld* GetWorld() const override;
	virtual int32 GetFunctionCallspace(UFunction* Function, FFrame* Stack) override;
	virtual bool CallRemoteFunction(UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack) override;
	virtual bool IsSupportedForNetworking() const override;
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) const override;
#endif
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty >& OutLifetimeProps) const override;
#if UE_WITH_IRIS
	virtual void RegisterReplicationFragments(UE::Net::FFragmentRegistrationContext& Context, UE::Net::EFragmentRegistrationFlags RegistrationFlags) override;
#endif
	//~End UObject

	//~Begin GameplayTaskComponent Events
	virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const override;
	virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const override;
	virtual AActor* GetGameplayTaskAvatar(const UGameplayTask* Task) const override;
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;
	//~End GameplayTaskComponent;

	//~Begin GameplayAbility

	// note by kun 2025.01.23
	// 添加GA模板(CDO);
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec);

	// note by kun 2025.01.23
	// 激活GA(创建GA实例)前的检查;
	virtual bool ShouldAbilityRespondToEvent(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayEventData* Payload) const;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;
	virtual bool ShouldActivateAbility(ENetRole Role) const;
	virtual bool DoesAbilitySatisfyTagRequirements(const UAbilitySystemComponent& AbilitySystemComponent, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;
	
	// note by kun 2025.01.23
	// GA实例被激活流程前，设置各类信息的时机;
	virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData = nullptr);
	virtual void SetCurrentActorInfo(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const;
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec);
	virtual void SetCurrentActivationInfo(const FGameplayAbilityActivationInfo ActivationInfo);
	
	// note by kun 2025.01.23
	// GA实例被激活流程后的流程起点;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	// CommitXXX可以理解为“经过‘抬手阶段(比如动画的前0.3s)’之后到了‘执行阶段’，最后检查是否满足执行的条件。”
	// 三套使用模式:
	// 1、单独Cooldown维度(CommitAbilityCooldown[CheckCooldown/ApplyCooldown])
	virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr);
	virtual bool CommitCheck(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr);
	virtual void CommitExecute(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo);
	// 2、单独Cost维度(CommitAbilityCost)
	virtual bool CommitAbilityCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const bool ForceCooldown, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr);
	virtual bool CheckCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const;
	virtual UGameplayEffect* GetCooldownGameplayEffect() const;
	// 3、上述俩一起检查(CommitAbility[CommitCheck/CommitExecute]
	virtual bool CommitAbilityCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr);
	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const;
	virtual UGameplayEffect* GetCostGameplayEffect() const;
	
	// note by kun 2025.01.23
	// GA实例终止执行流程的起点;
	// 注意:
	// 1、GA是允许在ActivateAbility流程里直接发起终止的，这个特性略坑;
	// 2、NotifyAbilityActivated是在PreActivate流程里产生的，用它作为上层逻辑GA激活判据可以但有二义性，需要配合NotifyAbilityFailed/NotifyAbilityEnded来做确认;
	// 3、最好是把能终止ActivateAbility的判断都写在CommitAbility流程里，这样就可以只根据NotifyAbilityCommit即可确认GA实例是否真的激活成功了;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility);

	// note by kun 2025.01.23
	// 移除GA模板(CDO);
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) {}

	// note by kun 2025.01.23
	// 
	virtual FGameplayEffectContextHandle MakeEffectContext(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const;
	virtual FGameplayEffectContextHandle GetContextFromOwner(FGameplayAbilityTargetDataHandle OptionalTargetData) const;
	virtual FGameplayEffectSpecHandle MakeOutgoingGameplayEffectSpec(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level = 1.f) const;

	// note by kun 2025.01.23
	// 将GA的DynamicAbilityTags 和 Owner的ASC的GameplayTagCountContainer 添加给GE的CapturedSourceTags;
	// 希望GA影响先前已存在的GE时可以用这种方式.
	virtual void ApplyAbilityTagsToGameplayEffectSpec(FGameplayEffectSpec& Spec, FGameplayAbilitySpec* AbilitySpec) const;

	// note by kun 2025.01.23
	// Cooldown相关的;
	// GAS的Cooldown本质是基于GE生命周期存在的。
	// 好处:
	// 1、能直接利用GE已实现的PredictionKey机制
	// 坏处:
	// 1、GE太重了
	// 2、"跨GA的公共CD"难以用一个CooldownGameplayEffectClass就代替
	// 3、配起来也啰嗦.
	virtual const FGameplayTagContainer* GetCooldownTags() const;
	// Cooldown相关的DebugHelper
	virtual float GetCooldownTimeRemaining(const FGameplayAbilityActorInfo* ActorInfo) const;
	virtual void GetCooldownTimeRemainingAndDuration(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, float& TimeRemaining, float& CooldownDuration) const;

	// note by kun 2025.01.23
	// ClientActivateAbilitySucceedWithEventData流程里的回调,主要涉及客户端先行Prediction的事务;
	virtual void ConfirmActivateSucceed();
	// PostNetInit可以认为EventData已经到达远端了;
	virtual void PostNetInit();

	// note by kun 2025.01.23
	// 我认为GA上的Montage相关接口是冗余的，GA不应该再保持一个montage的指针。因为如果有需要应该去扩展AbilityTask_PlayMontage,那边直接操作Montage实例;
	virtual void SetCurrentMontage(class UAnimMontage* InCurrentMontage);

	// note by kun 2025.01.23
	// ASC操作GA相关的接口;
	
	// RemoteEndOrCancelAbility流程中的行为;
	// 提前标注一下,但是如果本地的GA实例存在IsWaitingOnRemotePlayerdata==true的AbilityTask，又直接Cancel本地的GA实例
	// 这个杂糅行为，有点迷看不懂;
	virtual void SetRemoteInstanceHasEnded();
	// 是否参与fastarray rep的开关,感觉ServerOnly的GA可以用，从而减少ActivatedAbilities的尺寸;
	// 但为什么GAS自己不做这个事情呢?
	virtual bool ShouldReplicateAbilitySpec(const FGameplayAbilitySpec& AbilitySpec) const { return true; }
	// 清理一些由该GA创建的GE，GA默认不去负责GE的生命周期，只是互相持有Handle能通过ASC查到对方.
	virtual void RemoveGrantedByEffect();

	// note by kun 2025.01.23
	// GA操作ASC相关的接口;
	// 给ASC发事件的Helper;
	virtual void SendGameplayEvent(FGameplayTag EventTag, FGameplayEventData Payload);

	// note by kun 2025.01.23
	// AbilityTask操作GA相关的接口,AbilityTask实际跑起来可能需要跨帧,所以需要一些异步操作接口;
	// 双端交换数据的确认接口,主要是为了响应RemoteEndOrCancelAbility(RemoteInstanceEnded变量);
	virtual void NotifyAbilityTaskWaitingOnPlayerData(class UAbilityTask* AbilityTask);
	// 没Avatar就终止GA，也是狂野。个人感觉是一种TryCancel+Reason的Helper;
	virtual void NotifyAbilityTaskWaitingOnAvatar(class UAbilityTask* AbilityTask);
	// 疑似弃用时机，无实际调用;
	// GAS的逻辑是如果有Task需要Avatar，那这个GA还是死了好;
	virtual void NotifyAvatarDestroyed();

	// note by kun 2025.01.23
	// NonInstanced特供接口,为了运行时调整本GA和该ASC组件上其他GA的互斥关系;
	virtual bool IsBlockingOtherAbilities() const;
	virtual void SetShouldBlockOtherAbilities(bool bShouldBlockAbilities);
	virtual bool CanBeCanceled() const;
	virtual void SetCanBeCanceled(bool bCanBeCanceled);

	// note by kun 2025.01.23
	// Input相关的，属于管得太宽了，将来GAS自己肯定要废弃;
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) {};
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) {};
	virtual void OnWaitingForConfirmInputBegin() {}
	virtual void OnWaitingForConfirmInputEnd() {}

	//给蓝图用的版本;
	virtual bool K2_CommitAbility();
	virtual bool K2_CommitAbilityCooldown(bool BroadcastCommitEvent = false, bool ForceCooldown = false);
	virtual bool K2_CommitAbilityCost(bool BroadcastCommitEvent = false);
	virtual bool K2_CheckAbilityCooldown();
	virtual bool K2_CheckAbilityCost();
	virtual void K2_EndAbility();
	virtual void K2_EndAbilityLocally();
	virtual void K2_ExecuteGameplayCue(FGameplayTag GameplayCueTag, FGameplayEffectContextHandle Context);
	virtual void K2_ExecuteGameplayCueWithParams(FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameters);
	virtual void K2_AddGameplayCue(FGameplayTag GameplayCueTag, FGameplayEffectContextHandle Context, bool bRemoveOnAbilityEnd = true);
	virtual void K2_AddGameplayCueWithParams(FGameplayTag GameplayCueTag, const FGameplayCueParameters& GameplayCueParameter, bool bRemoveOnAbilityEnd = true);
	virtual void K2_RemoveGameplayCue(FGameplayTag GameplayCueTag);

	//~End GameplayAbility
#endif

	virtual bool DoesAbilitySatisfyTagRequirements(const UAbilitySystemComponent& AbilitySystemComponent, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
};
