//--------------------
// kun 2024.12.22
//--------------------

#include "BasePlayer.h"
#include "GameFramework/PlayerState.h"
#include "Components/SkeletalMeshComponent.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "Leeway/Component/BaseCharacterMovementComponent.h"
#include "Leeway/GameplayAbilities/BaseAbilitySystemComponent.h"
#include "Leeway/GameFramework/BasePlayerState.h"

ABasePlayer::ABasePlayer(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer.SetDefaultSubobjectClass<UBaseCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
}

void ABasePlayer::PossessedBy(AController* NewController)
{
    Super::PossessedBy(NewController);
    if (auto* PS = Cast<ABasePlayerState>(GetPlayerState()))
    {
        if (auto* GameASC = Cast<UGameAbilitySystemComponent>(PS->GetAbilitySystemComponent()))
        {
            GameASC->SetAvatarActor(this);
            ASC = GameASC;
        }
    }
}

void ABasePlayer::UnPossessed()
{
    if (auto* PS = Cast<ABasePlayerState>(GetPlayerState()))
    {
        if (auto* ASComp = PS->GetAbilitySystemComponent())
        {
            ASComp->SetAvatarActor(this);
            ASC.Reset();
        }
    }

    Super::UnPossessed();
}

void ABasePlayer::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void ABasePlayer::DebugDrawBones(FLinearColor Color) const
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

void ABasePlayer::DebugDrawBoneByName(FName BoneName, FLinearColor Color) const
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

void ABasePlayer::DebugDrawBoneByIndex(int BoneIndex, FLinearColor Color) const
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
