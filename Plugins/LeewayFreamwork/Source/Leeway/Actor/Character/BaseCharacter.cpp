//--------------------
// kun 2024.12.22
//--------------------

#include "BaseCharacter.h"
#include "Leeway/Component/BaseCharacterMovementComponent.h"
#include "Leeway/GameplayAbilities/AttributeSets/CombatAttributeSet.h"
#include "Leeway/GameplayAbilities/BaseAbilitySystemComponent.h"
#include "Leeway/GameFramework/LWGameplayTags.h"

DEFINE_LOG_CATEGORY(LogBaseCharacter);

ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UBaseCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
    , bRagdollEnabled(false)
{
    MainSkeletalMesh = GetMesh();
    MainSkeletalMesh->OnAnimInitialized.AddDynamic(this, &ThisClass::OnAnimInitialized);
    //CreatePartialMeshComponent(Head, TEXT("Head"), FTransform::Identity);
    //CreatePartialMeshComponent(Hair, TEXT("Hair"), FTransform::Identity);
    //CreatePartialMeshComponent(Torso, TEXT("Torso"), FTransform::Identity);
    //CreatePartialMeshComponent(Legs, TEXT("Legs"), FTransform::Identity);
    //CreatePartialMeshComponent(Hands, TEXT("Hands"), FTransform::Identity);
    //CreatePartialMeshComponent(Feet, TEXT("Feet"), FTransform::Identity);
    BaseCharacterMovement = GetCharacterMovement<UBaseCharacterMovementComponent>();
}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    //DOREPLIFETIME_CONDITION(ABaseCharacter, Stance, COND_SkipOwner);
    DOREPLIFETIME(ABaseCharacter, Stance);
    DOREPLIFETIME(ABaseCharacter, bRagdollEnabled);
}

void ABaseCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

void ABaseCharacter::BeginPlay()
{
    Super::BeginPlay();
    OnStanceChanged();
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
    return ASC.Get();
}

void ABaseCharacter::HandleGameplayEvent(FGameplayTag EventTag, FGameplayEventData Payload)
{
    HandleGameplayEvent(EventTag, &Payload);
}

void ABaseCharacter::HandleGameplayEvent(const FGameplayTag& EventTag, const FGameplayEventData* Payload)
{
    if (ASC.IsValid())
    {
        FScopedPredictionWindow NewScopedWindow(ASC.Get(), true);
        ASC->UAbilitySystemComponent::HandleGameplayEvent(EventTag, Payload);
    }
}

void ABaseCharacter::ChangeASC(UBaseAbilitySystemComponent* NewASC)
{
    if (NewASC != ASC)
    {
        if (ASC.IsValid())
        {
            PreUninitASC();
            {
                ASC->UninitAbilitySystem();
                ASC = nullptr;
            }
            PostUninitASC();
        }

        PreInitASC();
        {
            ASC = NewASC;
            if (ASC.IsValid())
            {
                ASC->SetAvatarActor(this);
                ASC->InitAbilitySystem(DA_AbilitySystem);
            }
        }
        PostInitASC();
    }
}

void ABaseCharacter::PreInitASC()
{
}

void ABaseCharacter::PostInitASC()
{
    if (ASC.IsValid())
    {
        // 对于客户端，该属性可能没来得及复制回来;
        // 可能对于客户端，需要新的“死亡事件源”;
        if (const auto* CombatAttributeSet = ASC->GetSet<UCombatAttributeSet>())
        {
            CombatAttributeSet->OnOutOfHealth.AddDynamic(this, &ThisClass::HandleOutOfHealth);
        }
    }
}

void ABaseCharacter::PreUninitASC()
{
}

void ABaseCharacter::PostUninitASC()
{
}

void ABaseCharacter::HandleOutOfHealth(const FOutOfHealthInfo& OutOfHealthInfo)
{
    if (ASC.IsValid())
    {
        FScopedPredictionWindow NewScopedWindow(ASC.Get(), true);
        FGameplayEventData PayLoad;
        ASC->HandleGameplayEvent(FLWGameplayTags::Get().GameEvent.Death, &PayLoad);
    }
}

void ABaseCharacter::CreatePartialMeshComponent(TObjectPtr<USkeletalMeshComponent>& Comp, FName Name, FTransform Trans)
{
    Comp = CreateDefaultSubobject<USkeletalMeshComponent>(Name);
    if (Comp)
    {
        Comp->AlwaysLoadOnClient = true;
        Comp->AlwaysLoadOnServer = true;
        Comp->bOwnerNoSee = false;
        Comp->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
        Comp->bCastDynamicShadow = true;
        Comp->bAffectDynamicIndirectLighting = true;
        Comp->PrimaryComponentTick.TickGroup = TG_PrePhysics;
        Comp->SetupAttachment(MainSkeletalMesh);
        Comp->SetLeaderPoseComponent(MainSkeletalMesh);
        static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
        Comp->SetCollisionProfileName(MeshCollisionProfileName);
        Comp->SetGenerateOverlapEvents(false);
        Comp->SetCanEverAffectNavigation(false);
    }
}

void ABaseCharacter::ChangeStance(const FGameplayTag& InStance)
{
    SetStance(InStance);
}

void ABaseCharacter::OnAnimInitialized()
{
    OnStanceChanged();
    //OnRagdollChanged();
}

void ABaseCharacter::SetStance(const FGameplayTag& Value)
{
    if (Stance != Value)
    {
        FGameplayTag OldValue = Stance;
        Stance = Value;
        OnStanceChanged(OldValue);
    }
}

void ABaseCharacter::OnStanceChanged(FGameplayTag PrevStanceTag)
{
    if (auto* MeshComp = GetMesh())
    {
        if (DA_LocomotionAnim)
        {
            if (PrevStanceTag != FGameplayTag::EmptyTag && PrevStanceTag != Stance)
            {
                if (auto* PrevABPClass = DA_LocomotionAnim->AnimSet.AnimLayersClasses.Find(PrevStanceTag))
                {
                    MeshComp->UnlinkAnimClassLayers(*PrevABPClass);
                }
            }
            if (auto* CurrentABPClass = DA_LocomotionAnim->AnimSet.AnimLayersClasses.Find(Stance))
            {
                MeshComp->LinkAnimClassLayers(*CurrentABPClass);
            }
        }
    }
}

void ABaseCharacter::SetRagdollEnable(bool Value)
{
    if (bRagdollEnabled != Value)
    {
        bool OldValue = bRagdollEnabled;
        bRagdollEnabled = Value;
        OnRagdollChanged(OldValue);
    }
}

void ABaseCharacter::OnRagdollChanged_Implementation(bool bPrevEnable)
{
    if (GetRagdollEnable())
    {
        if (auto* SKM = GetMesh())
        {
            RagdollOriginState.MeshTransform = SKM->GetRelativeTransform();
            RagdollOriginState.MeshCollisionEnabled = SKM->GetCollisionEnabled();

            SKM->SetAllBodiesSimulatePhysics(true);
            SKM->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

        }

        RagdollOriginState.MovementMode = GetCharacterMovement()->MovementMode;
        RagdollOriginState.CustomMovementMode = GetCharacterMovement()->CustomMovementMode;
        RagdollOriginState.CapsuleCollisionEnabled = GetCapsuleComponent()->GetCollisionEnabled();

        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        GetCharacterMovement()->DisableMovement();
    }
    else
    {
        if (auto* SKM = GetMesh())
        {
            SKM->SetRelativeTransform(RagdollOriginState.MeshTransform);
            SKM->SetAllBodiesSimulatePhysics(false);
            SKM->SetCollisionEnabled(RagdollOriginState.MeshCollisionEnabled);
        }

        GetCapsuleComponent()->SetCollisionEnabled(RagdollOriginState.CapsuleCollisionEnabled);
        GetCharacterMovement()->SetMovementMode(RagdollOriginState.MovementMode, RagdollOriginState.CustomMovementMode);
        //GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        //GetCharacterMovement()->SetDefaultMovementMode();
    }
}

void ABaseCharacter::DebugDrawBones(FLinearColor Color) const
{
    if (auto* SKMComp = GetMesh())
    {
        if (auto* SKM = SKMComp->GetSkeletalMeshAsset())
        {
            if (auto* PhysicsAsset = SKMComp->GetPhysicsAsset())
            {
                int BoneNum = SKM->GetRefSkeleton().GetNum();
                for (int iBone = 0, icBone = BoneNum; iBone < icBone; ++iBone)
                {
                    FName BoneName = SKM->GetRefSkeleton().GetBoneName(iBone);
                    if (auto* iBodySetupPtr = PhysicsAsset->BodySetupIndexMap.Find(BoneName))
                    {
                        int32 iBodySetup = *iBodySetupPtr;
                        if (auto* SkeletalBodySetup = PhysicsAsset->SkeletalBodySetups[iBodySetup].Get())
                        {
                            FTransform BoneToComponentTrans = SKMComp->GetBoneTransform(BoneName, ERelativeTransformSpace::RTS_Component);
                            FTransform ComponentToWorldTrans = SKMComp->GetComponentToWorld();
                            for (auto& Elem : SkeletalBodySetup->AggGeom.SphylElems)
                            {
                                FTransform ElemFT = Elem.GetTransform() * BoneToComponentTrans * ComponentToWorldTrans;
                                DrawDebugCapsule(GetWorld(), ElemFT.GetLocation(), 16, 6, ElemFT.Rotator().Quaternion(), FColor::Yellow, false, 5);
                            }
                        }
                    }
                }
            }
        }
    }
}

void ABaseCharacter::DebugDrawBoneByName(FName BoneName, FLinearColor Color) const
{
    if (auto* SKMComp = GetMesh())
    {
        if (auto* SKM = SKMComp->GetSkeletalMeshAsset())
        {
            if (auto* PhysicsAsset = SKMComp->GetPhysicsAsset())
            {
                if (auto* iBodySetupPtr = PhysicsAsset->BodySetupIndexMap.Find(BoneName))
                {
                    int32 iBodySetup = *iBodySetupPtr;
                    if (auto* SkeletalBodySetup = PhysicsAsset->SkeletalBodySetups[iBodySetup].Get())
                    {
                        FTransform BoneToComponentTrans = SKMComp->GetBoneTransform(BoneName, ERelativeTransformSpace::RTS_Component);
                        FTransform ComponentToWorldTrans = SKMComp->GetComponentToWorld();
                        for (auto& Elem : SkeletalBodySetup->AggGeom.SphylElems)
                        {
                            FTransform ElemFT = Elem.GetTransform() * BoneToComponentTrans * ComponentToWorldTrans;
                            DrawDebugCapsule(GetWorld(), ElemFT.GetLocation(), 16, 6, ElemFT.Rotator().Quaternion(), FColor::Yellow, false, 5);
                        }
                    }
                }
            }
        }
    }
}

void ABaseCharacter::DebugDrawBoneByIndex(int BoneIndex, FLinearColor Color) const
{
    if (auto* SKMComp = GetMesh())
    {
        if (auto* SKM = SKMComp->GetSkeletalMeshAsset())
        {
            if (auto* PhysicsAsset = SKMComp->GetPhysicsAsset())
            {
                FName BoneName = SKM->GetRefSkeleton().GetBoneName(BoneIndex);
                if (auto* iBodySetupPtr = PhysicsAsset->BodySetupIndexMap.Find(BoneName))
                {
                    int32 iBodySetup = *iBodySetupPtr;
                    if (auto* SkeletalBodySetup = PhysicsAsset->SkeletalBodySetups[iBodySetup].Get())
                    {
                        FTransform BoneToComponentTrans = SKMComp->GetBoneTransform(BoneName, ERelativeTransformSpace::RTS_Component);
                        FTransform ComponentToWorldTrans = SKMComp->GetComponentToWorld();
                        for (auto& Elem : SkeletalBodySetup->AggGeom.SphylElems)
                        {
                            FTransform ElemFT = Elem.GetTransform() * BoneToComponentTrans * ComponentToWorldTrans;
                            DrawDebugCapsule(GetWorld(), ElemFT.GetLocation(), 16, 6, ElemFT.Rotator().Quaternion(), FColor::Yellow, false, 5);
                        }
                    }
                }
            }
        }
    }
}
