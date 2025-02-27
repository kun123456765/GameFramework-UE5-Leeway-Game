//--------------------
// kun 2025.01.27
//--------------------

#pragma once

#include "Templates/SharedPointer.h"
#include "Components/SkeletalMeshComponent.h"
//#include "Engine/OverlapResult.h"
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
struct FLWClosestPointOnPhysicsAsset
{
    GENERATED_USTRUCT_BODY()

    /** The closest point in world space */
    UPROPERTY(BlueprintReadWrite)
    FVector ClosestWorldPosition = FVector::ZeroVector;

    /** The normal associated with the surface of the closest body */
    UPROPERTY(BlueprintReadWrite)
    FVector Normal = FVector::ZeroVector;

    /** The name of the bone associated with the closest body */
    UPROPERTY(BlueprintReadWrite)
    FName BoneName = NAME_None;

    /** The distance of the closest point and the original world position. 0 Indicates world position is inside the closest body. */
    UPROPERTY(BlueprintReadWrite)
    float Distance = -1.f;
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
        // û���Ǻ��Ƿ�ҪMultiComponents;
        //return HashCombine(GetTypeHash(Struct.Actor), GetTypeHash(Struct.Component), GetTypeHash(Struct.OverlapCenter), GetTypeHash(Struct.LastFrameOverlapCenter));
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
    UPROPERTY()
    FVector OverlapCenter;
    UPROPERTY()
    FVector LastFrameOverlapCenter;
    UPROPERTY()
    FLWClosestPointOnPhysicsAsset PhysicsAsset;
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


public:
    void ClearRuntimeVars()
    {
        OverlapedActors.Empty();
        LastFrameOverlapCenter = FVector::ZeroVector;
    }

    UPROPERTY(Transient)
    TSet<TWeakObjectPtr<AActor>> ConfirmedActors; // TWeakObjectPtr is not supported by blueprint;

    UPROPERTY(Transient)
    FVector LastFrameOverlapCenter;
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
