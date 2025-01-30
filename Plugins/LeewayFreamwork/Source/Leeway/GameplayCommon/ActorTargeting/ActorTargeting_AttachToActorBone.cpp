//--------------------
// kun 2025.01.26
//--------------------

#include "ActorTargeting_AttachToActorBone.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/GameInstance.h"
#include "Leeway/GameplayAbilities/Abilities/TargetActors/GATargetActor_MeleeWeapon.h"


void UActorTargeting_AttachToActorBone::PerformTargeting(FActorTargetingOwnerContext& OwnerContext)
{
    PerformTargetingStatic(OwnerContext);
}

void UActorTargeting_AttachToActorBone::PerformTargetingStatic(FActorTargetingOwnerContext& OwnerContext)
{
    if (const auto* ContextBase = OwnerContext.GetSubContext(FActorTargetingContext_AttachToActorBone::StaticStruct()))
    {
        const auto& Context = static_cast<const FActorTargetingContext_AttachToActorBone&>(*ContextBase);
        
        if (ACharacter* Character = Context.AttachToCharacter.Get())
        {
            FTransform WorldTransform = Context.AttachToCharacter->GetActorTransform();
            if (USkeletalMeshComponent* SKMComp = Character->GetMesh())
            {
                FTransform BoneToWorld = SKMComp->GetBoneTransform(Context.BoneName);
                for (const auto& GeomElem : OwnerContext.AggGeom.SphylElems)
                {
                    FTransform GeomToBone = GeomElem.GetTransform();

                    // 左右侧骨骼的offer是反的;
                    bool bRightSideBone = Context.BoneName.ToString().EndsWith("_r");
                    GeomToBone.SetTranslation(GeomToBone.GetTranslation() + GeomToBone.TransformVector(Context.Offset * (bRightSideBone ? -1 : 1)));
                    //GeomToBone.SetLocation(GeomToBone.GetLocation() + Context.Offset);
                    WorldTransform = GeomToBone * BoneToWorld;

                    OverlapMulti(OwnerContext, WorldTransform, GeomElem);
                }
            }
        }
    }
}

void UActorTargeting_AttachToActorBone::OverlapMulti(FActorTargetingOwnerContext& OwnerContext, const FTransform& WorldTransform, const FKSphylElem& CapsuleGeom)
{
    FCollisionObjectQueryParams QueryParams(FCollisionObjectQueryParams::AllDynamicObjects);
    QueryParams.AddObjectTypesToQuery(ECC_Pawn);
    QueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
    TArray<FOverlapResult> Overlaps;
    bool bHitted = OwnerContext.Owner.GetObject()->GetWorld()->OverlapMultiByObjectType(Overlaps, WorldTransform.GetLocation(), WorldTransform.Rotator().Quaternion(), QueryParams, FCollisionShape::MakeCapsule(CapsuleGeom.Radius, CapsuleGeom.Length * 0.5f));

    bool bHasValidTarget = false;
    const TArray<TWeakObjectPtr<AActor>>& IgnoreActors = OwnerContext.Owner.GetInterface()->GetSceneQueryIgnoreActors();
    for (auto& Overlap : Overlaps)
    {
        auto* Actor = Overlap.GetActor();
        if (Actor && !IgnoreActors.Contains(Actor))
        {
            if (auto* Comp = Overlap.GetComponent())
            {
                FTargetingResult_Overlap NetOverlap;
                NetOverlap.Actor = Actor;
                NetOverlap.Component = Comp;
                OwnerContext.OverlapedActors.Add(NetOverlap);

                if (!OwnerContext.ConfirmedActors.Contains(Actor))
                {
                    bHasValidTarget = true;
                }
            }
        }
    }

    bool Server = OwnerContext.Owner.GetObject()->GetWorld()->GetGameInstance()->IsDedicatedServerInstance();
    if (Server)
    {
        DrawDebugCapsule(OwnerContext.Owner.GetObject()->GetWorld(), WorldTransform.GetLocation(), CapsuleGeom.Length * 0.5f, CapsuleGeom.Radius, WorldTransform.Rotator().Quaternion(), bHasValidTarget ? FColor::Green : FColor::Red, false, 5);
    }
    else
    {
        DrawDebugCapsule(OwnerContext.Owner.GetObject()->GetWorld(), WorldTransform.GetLocation(), CapsuleGeom.Length * 0.5f, CapsuleGeom.Radius, WorldTransform.Rotator().Quaternion(), bHasValidTarget ? FColor::Green : FColor::Yellow, false, 5);
    }
}
