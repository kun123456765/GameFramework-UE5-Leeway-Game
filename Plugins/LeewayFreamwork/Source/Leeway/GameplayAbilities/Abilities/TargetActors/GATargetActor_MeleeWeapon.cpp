//--------------------
// kun 2025.01.26
//--------------------

#include "GATargetActor_MeleeWeapon.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Leeway/GameplayCommon/ActorTargeting/BaseActorTargeting.h"
#include "Leeway/GameplayCommon/ActorTargeting/ActorTargetingTypes.h"
#include "Leeway/GameplayCommon/ActorTargeting/ActorTargetingBlueprintLibrary.h"

#include "Components/PrimitiveComponent.h"

static FTargetingResult_Overlap& operator<<(FArchive& Ar, FTargetingResult_Overlap& Value)
{
    Ar << Value.Actor;
    Ar << Value.Component;

    return Value;
}

bool FTargetingResult_Overlap::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
    Ar << *this;
    return true;
}

bool FGameplayAbilityTargetData_LW_OverlapMulti::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
    SafeNetSerializeTArray_Default<31>(Ar, Overlaps);
    return true;
}

TArray<TWeakObjectPtr<AActor>> FGameplayAbilityTargetData_LW_OverlapMulti::GetActors() const
{
    TArray<TWeakObjectPtr<AActor>> Ret;
    for (auto& Overlap : Overlaps)
    {
        Ret.Emplace(Overlap.Actor);
    }
    return Ret;
}


void AGATargetActor_MeleeWeapon::StartTargeting(UGameplayAbility* InAbility)
{
    Super::StartTargeting(InAbility);
    TargetingOwnerContext.Owner = this;
    TargetingOwnerContext.AttachToActorBone.AttachToCharacter = Cast<ACharacter>(SourceActor.Get());
}

void AGATargetActor_MeleeWeapon::ConfirmTargeting()
{
    Super::ConfirmTargeting();
}

void AGATargetActor_MeleeWeapon::ConfirmTargetingAndContinue()
{
    Super::ConfirmTargetingAndContinue();
}

void AGATargetActor_MeleeWeapon::PerformTargetingQueue()
{
    PerformTargeting(TargetingOwnerContext);
    if (!TargetingOwnerContext.OverlapedActors.IsEmpty())
    {
        FGameplayAbilityTargetDataHandle DataHandle;
        if (MakeTargetData(DataHandle))
        {
            TargetDataReadyDelegate.Broadcast(DataHandle);
        }
    }
}

void AGATargetActor_MeleeWeapon::ClearConfirmedActors()
{
    TargetingOwnerContext.ConfirmedActors.Empty();
}

bool AGATargetActor_MeleeWeapon::MakeTargetData(FGameplayAbilityTargetDataHandle& DataHandle)
{
    TArray<FTargetingResult_Overlap*> TargetingResult;
    for (auto& OverlapedActor : TargetingOwnerContext.OverlapedActors)
    {
        if (!TargetingOwnerContext.ConfirmedActors.Contains(OverlapedActor.Actor.Get()))
        {
            TargetingOwnerContext.ConfirmedActors.Emplace(OverlapedActor.Actor.Get());
            TargetingResult.Emplace(&OverlapedActor);
        }
    }

    if (!TargetingResult.IsEmpty())
    {
        FGameplayAbilityTargetData_LW_OverlapMulti* DataPtr = new FGameplayAbilityTargetData_LW_OverlapMulti();
        for (const auto* OverlapedActor : TargetingResult)
        {
            DataPtr->Overlaps.Emplace(*OverlapedActor);
        }
        DataHandle.Add(DataPtr);
        return true;
    }

    return false;
}

void AGATargetActor_MeleeWeapon::PerformTargeting(FActorTargetingOwnerContext& Context)
{
    Super::PerformTargeting(Context);
}

const FActorTargetingContext* FActorTargetingOwnerContext_MeleeWeapon::GetSubContext(const UScriptStruct* SubContextClass) const
{
    if (SubContextClass == FActorTargetingContext_AttachToActorBone::StaticStruct())
    {
        return &AttachToActorBone;
    }
    else if (SubContextClass == FActorTargetingContext_AttachToActorBone::StaticStruct())
    {
        return &AttachToActorBone;
    }

    return nullptr;
}
