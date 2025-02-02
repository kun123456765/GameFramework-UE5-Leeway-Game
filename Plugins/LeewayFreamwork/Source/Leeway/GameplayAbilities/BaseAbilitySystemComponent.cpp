//--------------------
// kun 2025.01.23
//--------------------

#include "BaseAbilitySystemComponent.h"
#include "Leeway/GameplayAbilities/AttributeSets/CombatAttributeSet.h"

namespace NSLeeway
{

#define Text_LogLevelHelp TEXT("[0/1/2]")
#define Text_NumericalHelp TEXT("[=,!,<,>,*] [String]")
#define Text_StringHelp TEXT("[=,!,<,>,c,n,s,e,*] [String]")


    class FLWIntACC : FAutoConsoleCommandWithWorldArgsAndOutputDevice
    {
    public:
        FLWIntACC(const TCHAR* Name, uint32 Mod, uint32 Flags = ECVF_Default)
            :FAutoConsoleCommandWithWorldArgsAndOutputDevice(Name
                , Text_LogLevelHelp
                , FConsoleCommandWithWorldArgsAndOutputDeviceDelegate::CreateRaw(this, &FLWIntACC::Command)
                , Flags)
        {
        }

        inline bool operator >(int Ohter)
        {
            return Value > Ohter;
        }

    private:
        void Command(const TArray<FString>& Args, UWorld* World, FOutputDevice& Output)
        {
            if (Args.IsValidIndex(0))
            {
                if (!Args[0].IsEmpty())
                {
                    LexFromString(Value, *Args[0]);
                    return;
                }
            }

            if (Mod > 0)
            {
                Value = (Value + 1) % Mod;
            }
            else
            {
                Value = 0;
            }
        }
    
    private:
        int32 Value = 0;
        int32 Mod = 0;
    };

    static FLWIntACC ASCLogLevel(TEXT("lw.debug.asc.comp.log"), ECVF_Default);
    static FLWIntACC GALogLevel(TEXT("lw.debug.asc.ga.log"), ECVF_Default);
    static FLWIntACC MontageLogLevel(TEXT("lw.debug.asc.montage.log"), ECVF_Default);
}

void UBaseAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
    UE_CLOG_EX(NSLeeway::ASCLogLevel, LogAbilitySystemComponent, Log, TEXT("InitAbilityActorInfo"));

    bool bNeedRebuildGranted = false;
    if (IsOwnerActorAuthoritative() && (InOwnerActor != GetOwnerActor() || InAvatarActor != GetAvatarActor()))
    {
        if (InAvatarActor->IsA<APlayerState>())
        {
            // Player的放在 Character::PlayerStateChanged 流程里做;
            bNeedRebuildGranted = false;
        }
        else
        {
            bNeedRebuildGranted = true;
        }
    }

    Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

    if (bNeedRebuildGranted)
    {
        InitGrantedByDataAsset(InOwnerActor, InAvatarActor);
    }
}

void UBaseAbilitySystemComponent::ClearActorInfo()
{
    UE_CLOG_EX(NSLeeway::ASCLogLevel, LogAbilitySystemComponent, Log, TEXT("ClearActorInfo"));
    
    UninitAllGrantedAndInstancedObjects();
    Super::ClearActorInfo();
}

void UBaseAbilitySystemComponent::NotifyAbilityCommit(UGameplayAbility* Ability)
{
    UE_CLOG_EX(NSLeeway::GALogLevel, LogAbilitySystemComponent, Log, TEXT("NotifyAbilityCommit"));
    Super::NotifyAbilityCommit(Ability);
}

void UBaseAbilitySystemComponent::NotifyAbilityActivated(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability)
{
    UE_CLOG_EX(NSLeeway::GALogLevel, LogAbilitySystemComponent, Log, TEXT("NotifyAbilityActivated"));
    Super::NotifyAbilityActivated(Handle, Ability);
}

void UBaseAbilitySystemComponent::NotifyAbilityFailed(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability, const FGameplayTagContainer& FailureReason)
{
    UE_CLOG_EX(NSLeeway::GALogLevel, LogAbilitySystemComponent, Log, TEXT("NotifyAbilityFailed"));
    Super::NotifyAbilityFailed(Handle, Ability, FailureReason);
}

float UBaseAbilitySystemComponent::PlayMontage(UGameplayAbility* AnimatingAbility, FGameplayAbilityActivationInfo ActivationInfo, UAnimMontage* Montage, float InPlayRate, FName StartSectionName, float StartTimeSeconds)
{
    UE_CLOG_EX(NSLeeway::MontageLogLevel, LogAbilitySystemComponent, Log, TEXT("PlayMontage"));
    return Super::PlayMontage(AnimatingAbility, ActivationInfo, Montage, InPlayRate, StartSectionName, StartTimeSeconds);
}

UAnimMontage* UBaseAbilitySystemComponent::PlaySlotAnimationAsDynamicMontage(UGameplayAbility* AnimatingAbility, FGameplayAbilityActivationInfo ActivationInfo, UAnimSequenceBase* AnimAsset, FName SlotName, float BlendInTime, float BlendOutTime, float InPlayRate, float StartTimeSeconds)
{
    UE_CLOG_EX(NSLeeway::MontageLogLevel, LogAbilitySystemComponent, Log, TEXT("PlaySlotAnimationAsDynamicMontage"));
    return Super::PlaySlotAnimationAsDynamicMontage(AnimatingAbility, ActivationInfo, AnimAsset, SlotName, BlendInTime, BlendOutTime, InPlayRate, StartTimeSeconds);
}

float UBaseAbilitySystemComponent::PlayMontageSimulated(UAnimMontage* Montage, float InPlayRate, FName StartSectionName)
{
    UE_CLOG_EX(NSLeeway::MontageLogLevel, LogAbilitySystemComponent, Log, TEXT("PlayMontageSimulated"));
    return Super::PlayMontageSimulated(Montage, InPlayRate, StartSectionName);
}

UAnimMontage* UBaseAbilitySystemComponent::PlaySlotAnimationAsDynamicMontageSimulated(UAnimSequenceBase* AnimAsset, FName SlotName, float BlendInTime, float BlendOutTime, float InPlayRate)
{
    UE_CLOG_EX(NSLeeway::MontageLogLevel, LogAbilitySystemComponent, Log, TEXT("PlaySlotAnimationAsDynamicMontageSimulated"));
    return Super::PlaySlotAnimationAsDynamicMontageSimulated(AnimAsset, SlotName, BlendInTime, BlendOutTime, InPlayRate);
}

void UBaseAbilitySystemComponent::CurrentMontageStop(float OverrideBlendOutTime)
{
    UE_CLOG_EX(NSLeeway::MontageLogLevel, LogAbilitySystemComponent, Log, TEXT("CurrentMontageStop"));
    return Super::CurrentMontageStop(OverrideBlendOutTime);
}

void UBaseAbilitySystemComponent::StopMontageIfCurrent(const UAnimMontage& Montage, float OverrideBlendOutTime)
{
    UE_CLOG_EX(NSLeeway::MontageLogLevel, LogAbilitySystemComponent, Log, TEXT("StopMontageIfCurrent"));
    return Super::StopMontageIfCurrent(Montage, OverrideBlendOutTime);
}

void UBaseAbilitySystemComponent::ClearAnimatingAbility(UGameplayAbility* Ability)
{
    UE_CLOG_EX(NSLeeway::MontageLogLevel, LogAbilitySystemComponent, Log, TEXT("ClearAnimatingAbility"));
    return Super::ClearAnimatingAbility(Ability);
}

void UBaseAbilitySystemComponent::CurrentMontageJumpToSection(FName SectionName)
{
    UE_CLOG_EX(NSLeeway::MontageLogLevel, LogAbilitySystemComponent, Log, TEXT("CurrentMontageJumpToSection"));
    return Super::CurrentMontageJumpToSection(SectionName);
}

void UBaseAbilitySystemComponent::CurrentMontageSetNextSectionName(FName FromSectionName, FName ToSectionName)
{
    UE_CLOG_EX(NSLeeway::MontageLogLevel, LogAbilitySystemComponent, Log, TEXT("CurrentMontageSetNextSectionName"));
    return Super::CurrentMontageSetNextSectionName(FromSectionName, ToSectionName);
}

void UBaseAbilitySystemComponent::CurrentMontageSetPlayRate(float InPlayRate)
{
    UE_CLOG_EX(NSLeeway::MontageLogLevel, LogAbilitySystemComponent, Log, TEXT("CurrentMontageSetPlayRate"));
    return Super::CurrentMontageSetPlayRate(InPlayRate);
}

void UBaseAbilitySystemComponent::OnRep_ReplicatedAnimMontage()
{
    UE_CLOG_EX(NSLeeway::MontageLogLevel, LogAbilitySystemComponent, Log, TEXT("OnRep_ReplicatedAnimMontage"));
    Super::OnRep_ReplicatedAnimMontage();
}

void UBaseAbilitySystemComponent::InitGrantedByDataAsset(AActor* InOwnerActor, AActor* InAvatarActor)
{
    if (DA_AbilitySystem)
    {
        bool bIsAuthority = GetOwner()->GetLocalRole() == ENetRole::ROLE_Authority;
        bool bIsAutonomous = GetOwner()->GetLocalRole() == ENetRole::ROLE_AutonomousProxy;
        bool bIsSimulated = GetOwner()->GetLocalRole() == ENetRole::ROLE_SimulatedProxy;

        if (bIsAuthority)
        {
            if (DA_AbilitySystem->GrantedSet.AttriSetSet.AttriSets.Num() > 0)
            {
                TArray<UAttributeSet*> NewAttriSets;
                for (const TSubclassOf<UAttributeSet> AttriSetClass : DA_AbilitySystem->GrantedSet.AttriSetSet.AttriSets)
                {
                    UAttributeSet* NewAttriSet = NewObject<UAttributeSet>(GetOwner(), AttriSetClass);
                    NewAttriSets.Add(NewAttriSet);
                }
                SetSpawnedAttributes(NewAttriSets);

                if (auto* AttrSet = Cast<UCombatAttributeSet>(GetAttributeSet(UCombatAttributeSet::StaticClass())))
                {
                    const float MaxHP = 1000;
                    const_cast<UCombatAttributeSet*>(AttrSet)->Initialize(MaxHP);
                    //SetNumericAttributeBase(AttrSet->GetHealthAttribute(), HP);
                    //SetNumericAttributeBase(AttrSet->GetMaxHealthAttribute(), HP);
                }
            }
        }

        for (const FGrantedAbility& GrantedAbility : DA_AbilitySystem->GrantedSet.AbilitySet.Abilities)
        {
            auto* CDO_Ability = GrantedAbility.AbilityClass->GetDefaultObject<UGameplayAbility>();
            auto NetExecutionPolicy = CDO_Ability->GetNetExecutionPolicy();
            bool bIsLocalOnlyGA = EGameplayAbilityNetExecutionPolicy::Type::LocalOnly == NetExecutionPolicy;
            bool bCanGive = (bIsAuthority && !bIsLocalOnlyGA) // 服务器添加;
                || ((bIsAutonomous || bIsSimulated) && bIsLocalOnlyGA); // 纯客户端，当前端添加;
            {
                if (bCanGive)
                {
                    FGameplayAbilitySpec NewAbilitySpec = BuildAbilitySpecFromClass(GrantedAbility.AbilityClass, GrantedAbility.Level);
                    auto GAHandle = GiveAbility(NewAbilitySpec);
                    GrantedHandleSet.Abilities.Add(GAHandle);
                }
            }
        }
    }
}

void UBaseAbilitySystemComponent::UninitAllGrantedAndInstancedObjects()
{
    CancelAbilities();
    ClearAllAbilities();
    RemoveActiveEffects(FGameplayEffectQuery(), -1);
    RemoveAllGameplayCues();
}
