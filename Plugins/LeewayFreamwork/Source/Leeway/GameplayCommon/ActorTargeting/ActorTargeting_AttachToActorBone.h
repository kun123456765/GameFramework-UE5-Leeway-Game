//--------------------
// kun 2025.01.26
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BaseActorTargeting.h"
#include "ActorTargeting_AttachToActorBone.generated.h"

USTRUCT(BlueprintType)
struct FActorTargetingContext_AttachToActorBone : public FActorTargetingContext
{
    GENERATED_USTRUCT_BODY()


    virtual UScriptStruct* GetScriptStruct() const override
    {
        return FActorTargetingContext_AttachToActorBone::StaticStruct();
    }

    UPROPERTY(BlueprintReadWrite)
    TWeakObjectPtr<class ACharacter> AttachToCharacter;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FName BoneName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FVector Offset = FVector(0, 42.f, 0);
};

UCLASS(MinimalAPI)
class UActorTargeting_AttachToActorBone : public UBaseActorTargeting
{
    GENERATED_BODY()

public:
    virtual void PerformTargeting(FActorTargetingOwnerContext& OwnerContext) override;

private:
    static void PerformTargetingStatic(FActorTargetingOwnerContext& Context);
    static void OverlapMulti(FActorTargetingOwnerContext& OwnerContext, const FTransform& WorldTransform, const FKSphylElem& CapsuleGeom);
};
