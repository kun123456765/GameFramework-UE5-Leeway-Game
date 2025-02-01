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
	// ����̳�,����ϸ�ھͻ�����;
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
	// ���GAģ��(CDO);
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec);

	// note by kun 2025.01.23
	// ����GA(����GAʵ��)ǰ�ļ��;
	virtual bool ShouldAbilityRespondToEvent(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayEventData* Payload) const;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;
	virtual bool ShouldActivateAbility(ENetRole Role) const;
	virtual bool DoesAbilitySatisfyTagRequirements(const UAbilitySystemComponent& AbilitySystemComponent, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;
	
	// note by kun 2025.01.23
	// GAʵ������������ǰ�����ø�����Ϣ��ʱ��;
	virtual void PreActivate(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, FOnGameplayAbilityEnded::FDelegate* OnGameplayAbilityEndedDelegate, const FGameplayEventData* TriggerEventData = nullptr);
	virtual void SetCurrentActorInfo(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const;
	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec);
	virtual void SetCurrentActivationInfo(const FGameplayAbilityActivationInfo ActivationInfo);
	
	// note by kun 2025.01.23
	// GAʵ�����������̺���������;
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData);
	// CommitXXX�������Ϊ��������̧�ֽ׶�(���綯����ǰ0.3s)��֮���ˡ�ִ�н׶Ρ���������Ƿ�����ִ�е���������
	// ����ʹ��ģʽ:
	// 1������Cooldownά��(CommitAbilityCooldown[CheckCooldown/ApplyCooldown])
	virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr);
	virtual bool CommitCheck(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr);
	virtual void CommitExecute(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo);
	// 2������Costά��(CommitAbilityCost)
	virtual bool CommitAbilityCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const bool ForceCooldown, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr);
	virtual bool CheckCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const;
	virtual UGameplayEffect* GetCooldownGameplayEffect() const;
	// 3��������һ����(CommitAbility[CommitCheck/CommitExecute]
	virtual bool CommitAbilityCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr);
	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const;
	virtual UGameplayEffect* GetCostGameplayEffect() const;
	
	// note by kun 2025.01.23
	// GAʵ����ִֹ�����̵����;
	// ע��:
	// 1��GA��������ActivateAbility������ֱ�ӷ�����ֹ�ģ���������Կ�;
	// 2��NotifyAbilityActivated����PreActivate����������ģ�������Ϊ�ϲ��߼�GA�����оݿ��Ե��ж����ԣ���Ҫ���NotifyAbilityFailed/NotifyAbilityEnded����ȷ��;
	// 3������ǰ�����ֹActivateAbility���ж϶�д��CommitAbility����������Ϳ���ֻ����NotifyAbilityCommit����ȷ��GAʵ���Ƿ���ļ���ɹ���;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);
	virtual void CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility);

	// note by kun 2025.01.23
	// �Ƴ�GAģ��(CDO);
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) {}

	// note by kun 2025.01.23
	// 
	virtual FGameplayEffectContextHandle MakeEffectContext(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo) const;
	virtual FGameplayEffectContextHandle GetContextFromOwner(FGameplayAbilityTargetDataHandle OptionalTargetData) const;
	virtual FGameplayEffectSpecHandle MakeOutgoingGameplayEffectSpec(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level = 1.f) const;

	// note by kun 2025.01.23
	// ��GA��DynamicAbilityTags �� Owner��ASC��GameplayTagCountContainer ��Ӹ�GE��CapturedSourceTags;
	// ϣ��GAӰ����ǰ�Ѵ��ڵ�GEʱ���������ַ�ʽ.
	virtual void ApplyAbilityTagsToGameplayEffectSpec(FGameplayEffectSpec& Spec, FGameplayAbilitySpec* AbilitySpec) const;

	// note by kun 2025.01.23
	// Cooldown��ص�;
	// GAS��Cooldown�����ǻ���GE�������ڴ��ڵġ�
	// �ô�:
	// 1����ֱ������GE��ʵ�ֵ�PredictionKey����
	// ����:
	// 1��GE̫����
	// 2��"��GA�Ĺ���CD"������һ��CooldownGameplayEffectClass�ʹ���
	// 3��������Ҳ����.
	virtual const FGameplayTagContainer* GetCooldownTags() const;
	// Cooldown��ص�DebugHelper
	virtual float GetCooldownTimeRemaining(const FGameplayAbilityActorInfo* ActorInfo) const;
	virtual void GetCooldownTimeRemainingAndDuration(FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, float& TimeRemaining, float& CooldownDuration) const;

	// note by kun 2025.01.23
	// ClientActivateAbilitySucceedWithEventData������Ļص�,��Ҫ�漰�ͻ�������Prediction������;
	virtual void ConfirmActivateSucceed();
	// PostNetInit������ΪEventData�Ѿ�����Զ����;
	virtual void PostNetInit();

	// note by kun 2025.01.23
	// ����ΪGA�ϵ�Montage��ؽӿ�������ģ�GA��Ӧ���ٱ���һ��montage��ָ�롣��Ϊ�������ҪӦ��ȥ��չAbilityTask_PlayMontage,�Ǳ�ֱ�Ӳ���Montageʵ��;
	virtual void SetCurrentMontage(class UAnimMontage* InCurrentMontage);

	// note by kun 2025.01.23
	// ASC����GA��صĽӿ�;
	
	// RemoteEndOrCancelAbility�����е���Ϊ;
	// ��ǰ��עһ��,����������ص�GAʵ������IsWaitingOnRemotePlayerdata==true��AbilityTask����ֱ��Cancel���ص�GAʵ��
	// ���������Ϊ���е��Կ�����;
	virtual void SetRemoteInstanceHasEnded();
	// �Ƿ����fastarray rep�Ŀ���,�о�ServerOnly��GA�����ã��Ӷ�����ActivatedAbilities�ĳߴ�;
	// ��ΪʲôGAS�Լ��������������?
	virtual bool ShouldReplicateAbilitySpec(const FGameplayAbilitySpec& AbilitySpec) const { return true; }
	// ����һЩ�ɸ�GA������GE��GAĬ�ϲ�ȥ����GE���������ڣ�ֻ�ǻ������Handle��ͨ��ASC�鵽�Է�.
	virtual void RemoveGrantedByEffect();

	// note by kun 2025.01.23
	// GA����ASC��صĽӿ�;
	// ��ASC���¼���Helper;
	virtual void SendGameplayEvent(FGameplayTag EventTag, FGameplayEventData Payload);

	// note by kun 2025.01.23
	// AbilityTask����GA��صĽӿ�,AbilityTaskʵ��������������Ҫ��֡,������ҪһЩ�첽�����ӿ�;
	// ˫�˽������ݵ�ȷ�Ͻӿ�,��Ҫ��Ϊ����ӦRemoteEndOrCancelAbility(RemoteInstanceEnded����);
	virtual void NotifyAbilityTaskWaitingOnPlayerData(class UAbilityTask* AbilityTask);
	// ûAvatar����ֹGA��Ҳ�ǿ�Ұ�����˸о���һ��TryCancel+Reason��Helper;
	virtual void NotifyAbilityTaskWaitingOnAvatar(class UAbilityTask* AbilityTask);
	// ��������ʱ������ʵ�ʵ���;
	// GAS���߼��������Task��ҪAvatar�������GA�������˺�;
	virtual void NotifyAvatarDestroyed();

	// note by kun 2025.01.23
	// NonInstanced�ع��ӿ�,Ϊ������ʱ������GA�͸�ASC���������GA�Ļ����ϵ;
	virtual bool IsBlockingOtherAbilities() const;
	virtual void SetShouldBlockOtherAbilities(bool bShouldBlockAbilities);
	virtual bool CanBeCanceled() const;
	virtual void SetCanBeCanceled(bool bCanBeCanceled);

	// note by kun 2025.01.23
	// Input��صģ����ڹܵ�̫���ˣ�����GAS�Լ��϶�Ҫ����;
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) {};
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) {};
	virtual void OnWaitingForConfirmInputBegin() {}
	virtual void OnWaitingForConfirmInputEnd() {}

	//����ͼ�õİ汾;
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
