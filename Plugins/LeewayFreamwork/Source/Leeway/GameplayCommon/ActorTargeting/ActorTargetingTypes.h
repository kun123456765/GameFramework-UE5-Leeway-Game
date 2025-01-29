//--------------------
// kun 2025.01.27
//--------------------

#pragma once

#include "Templates/SharedPointer.h"
#include "Engine/OverlapResult.h"
#include "PhysicsEngine/AggregateGeom.h"

#include "ActorTargetingTypes.generated.h"

USTRUCT(BlueprintType)
struct FActorTargetingContext
{
    GENERATED_USTRUCT_BODY()

    virtual ~FActorTargetingContext() {}

    virtual UScriptStruct* GetScriptStruct() const { return FActorTargetingContext::StaticStruct(); }
};

USTRUCT(BlueprintType)
struct FLWAggregateGeom
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, Category = "Aggregate Geometry", meta = (DisplayName = "Spheres"))
    TArray<FKSphereElem> SphereElems;

    UPROPERTY(EditAnywhere, Category = "Aggregate Geometry", meta = (DisplayName = "Boxes"))
    TArray<FKBoxElem> BoxElems;

    UPROPERTY(EditAnywhere, Category = "Aggregate Geometry", meta = (DisplayName = "Capsules"))
    TArray<FKSphylElem> SphylElems;

    UPROPERTY(EditAnywhere, Category = "Aggregate Geometry", meta = (DisplayName = "Convex Elements"))
    TArray<FKConvexElem> ConvexElems;

    UPROPERTY(EditAnywhere, Category = "Aggregate Geometry", meta = (DisplayName = "Tapered Capsules"))
    TArray<FKTaperedCapsuleElem> TaperedCapsuleElems;

    UPROPERTY(EditAnywhere, Category = "Aggregate Geometry", meta = (DisplayName = "Level Sets"))
    TArray<FKLevelSetElem> LevelSetElems;

    UPROPERTY(EditAnywhere, Category = "Aggregate Geometry", meta = (DisplayName = "(Experimental) Skinned Level Sets"), Experimental)
    TArray<FKSkinnedLevelSetElem> SkinnedLevelSetElems;
};

USTRUCT(BlueprintType)
struct FTargetingResult_Overlap
{
    GENERATED_USTRUCT_BODY()

public:
    friend uint32 GetTypeHash(const FTargetingResult_Overlap& Struct)
    {
        return GetTypeHash(Struct.Actor);
        // note by kun 2025.01.28
        // 没考虑好是否要MultiComponents;
        //return HashCombine(GetTypeHash(Struct.Actor), GetTypeHash(Struct.Component));
    }

    bool operator==(const FTargetingResult_Overlap& Other) const
    {
        return Actor == Other.Actor;
    }

public:
    bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
    virtual FString ToString() const { return TEXT("FTargetingResult_Overlap"); }

public:
    UPROPERTY()
    TWeakObjectPtr<AActor> Actor;
    UPROPERTY()
    TWeakObjectPtr<UPrimitiveComponent> Component;
};
template<>
struct TStructOpsTypeTraits<FTargetingResult_Overlap> : public TStructOpsTypeTraitsBase2<FTargetingResult_Overlap>
{
    enum
    {
        WithNetSerializer = true
    };
};

USTRUCT(BlueprintType)
struct FActorTargetingOwnerContext : public FActorTargetingContext
{
    GENERATED_USTRUCT_BODY()

    virtual UScriptStruct* GetScriptStruct() const override { return FActorTargetingOwnerContext::StaticStruct(); }
    virtual const FActorTargetingContext* GetSubContext(const UScriptStruct* SubContextClass) const PURE_VIRTUAL(FActorTargetingOwnerContext::GetSubContext, return nullptr;);

    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (DisplayName = "Primitives"))
    FLWAggregateGeom AggGeom;


    //--------------------
    // runtime data;
    //--------------------
public:
    UPROPERTY(BlueprintReadWrite, Transient)
    TScriptInterface<class IActorTargetingOwnerInterface> Owner;

    UPROPERTY(BlueprintReadWrite, Transient)
    TSet<FTargetingResult_Overlap> OverlapedActors;

    UPROPERTY(Transient)
    TSet<TWeakObjectPtr<AActor>> ConfirmedActors; // TWeakObjectPtr is not supported by blueprint;
};

UENUM()
enum class EActorTargetingTypeBit : uint8
{
    AttachToActorBoneFlag,
};

UENUM()
enum class EActorTargetingType : uint32
{
    AttachToActorBone = 1 << (uint8)EActorTargetingTypeBit::AttachToActorBoneFlag,
};

UENUM()
enum class EActorTargetingContextType : uint32
{
    AttachToActorBone = 1 << (uint8)EActorTargetingTypeBit::AttachToActorBoneFlag,
};
