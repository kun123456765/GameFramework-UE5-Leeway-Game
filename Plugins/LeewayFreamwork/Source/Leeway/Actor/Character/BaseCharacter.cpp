//--------------------
// kun 2024.12.22
//--------------------

#include "BaseCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Leeway/GameplayAbilities/BaseAbilitySystemComponent.h"

DEFINE_LOG_CATEGORY(LogBaseCharacter);


ABaseCharacter::ABaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    MainSkeletalMesh = GetMesh();
    if (MainSkeletalMesh)
    {
        //CreatePartialMeshComponent(Head, TEXT("Head"), FTransform::Identity);
        //CreatePartialMeshComponent(Hair, TEXT("Hair"), FTransform::Identity);
        //CreatePartialMeshComponent(Torso, TEXT("Torso"), FTransform::Identity);
        //CreatePartialMeshComponent(Legs, TEXT("Legs"), FTransform::Identity);
        //CreatePartialMeshComponent(Hands, TEXT("Hands"), FTransform::Identity);
        //CreatePartialMeshComponent(Feet, TEXT("Feet"), FTransform::Identity);
    }
}

void ABaseCharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

inline UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
    return ASC.Get();
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
