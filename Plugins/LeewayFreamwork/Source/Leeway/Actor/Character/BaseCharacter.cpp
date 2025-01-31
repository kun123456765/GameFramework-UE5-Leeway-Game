//--------------------
// kun 2024.12.22
//--------------------

#include "BaseCharacter.h"
#include "Leeway/Component/BaseCharacterMovementComponent.h"
#include "Leeway/GameplayAbilities/BaseAbilitySystemComponent.h"

DEFINE_LOG_CATEGORY(LogBaseCharacter);


ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UBaseCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
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

    DOREPLIFETIME(ABaseCharacter, Stance);
    //DOREPLIFETIME_CONDITION(ABaseCharacter, Stance, COND_SkipOwner);
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

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
    return ASC.Get();
}

void ABaseCharacter::OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState)
{
    if (LastPlayerState != OldPlayerState)
    {
        LastPlayerState = OldPlayerState;
    }
    OnPlayerStateChangedImpl(NewPlayerState, LastPlayerState.Get());
}

void ABaseCharacter::OnPlayerStateChangedImpl(APlayerState* NewPlayerState, APlayerState* OldPlayerState)
{
    auto* OldASC = OldPlayerState ? (OldPlayerState->Implements<UAbilitySystemInterface>() ? Cast<UBaseAbilitySystemComponent>(Cast<IAbilitySystemInterface>(OldPlayerState)->GetAbilitySystemComponent()) : nullptr) : nullptr;
    auto* CurASC = NewPlayerState ? (NewPlayerState->Implements<UAbilitySystemInterface>() ? Cast<UBaseAbilitySystemComponent>(Cast<IAbilitySystemInterface>(NewPlayerState)->GetAbilitySystemComponent()) : nullptr) : nullptr;

    if (OldASC != CurASC)
    {
        //todo kun 2025.01.31
        // how to reset the previous ability system component?
    }

    if (CurASC)
    {
        CurASC->SetAvatarActor(this);
    }

    ASC = CurASC;
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
}

const FGameplayTag& ABaseCharacter::GetStance() const
{
    return Stance;
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

void ABaseCharacter::OnRep_Stance(FGameplayTag PrevStanceTag)
{
    OnStanceChanged(PrevStanceTag);
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
