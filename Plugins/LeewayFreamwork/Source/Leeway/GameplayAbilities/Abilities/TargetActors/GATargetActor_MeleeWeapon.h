//--------------------
// kun 2025.01.26
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbilityTargetActor.h"

#include "Abilities/GameplayAbilityTargetActor.h"
#include "Engine/OverlapResult.h"

#include "Leeway/GameplayCommon/ActorTargeting/ActorTargetingOwnerInterface.h"
#include "Leeway/GameplayCommon/ActorTargeting/ActorTargeting_AttachToActorBone.h"


#include "GATargetActor_MeleeWeapon.generated.h"


struct FActorTargetingContext;

USTRUCT(BlueprintType)
struct FGameplayAbilityTargetData_LW_OverlapMulti : public FGameplayAbilityTargetData
{
    GENERATED_USTRUCT_BODY()

public:
    bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

    virtual FString ToString() const override
    {
        return TEXT("FGameplayAbilityTargetData_LW_OverlapMulti");
    }

    virtual UScriptStruct* GetScriptStruct() const override
    {
        return FGameplayAbilityTargetData_LW_OverlapMulti::StaticStruct();
    }

    virtual TArray<TWeakObjectPtr<AActor>> GetActors() const override;
public:
    UPROPERTY()
    TArray<FTargetingResult_Overlap> Overlaps;
};

template<>
struct TStructOpsTypeTraits<FGameplayAbilityTargetData_LW_OverlapMulti> : public TStructOpsTypeTraitsBase2<FGameplayAbilityTargetData_LW_OverlapMulti>
{
    enum
    {
        WithNetSerializer = true
    };
};

USTRUCT(BlueprintType)
struct FActorTargetingOwnerContext_MeleeWeapon : public FActorTargetingOwnerContext
{
    GENERATED_USTRUCT_BODY()

    virtual const FActorTargetingContext* GetSubContext(const UScriptStruct* SubContextClass) const override;

    virtual UScriptStruct* GetScriptStruct() const
    {
        return FActorTargetingOwnerContext_MeleeWeapon::StaticStruct();
    }

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FActorTargetingContext_AttachToActorBone AttachToActorBone;
};

UCLASS(MinimalAPI, Blueprintable)
class AGATargetActor_MeleeWeapon : public ABaseGameplayAbilityTargetActor
{
    GENERATED_BODY()

#pragma region ActorTargeting
    // ~Begin GameplayAbilityTargetActor
public:
    virtual void StartTargeting(UGameplayAbility* InAbility) override;
    virtual void ConfirmTargeting() override;
    virtual void ConfirmTargetingAndContinue() override;
    // ~End GameplayAbilityTargetActor
#pragma region ActorTargeting

#pragma region ActorTargeting
    // ~Begin ActorTargeting
protected:
    virtual void PerformTargeting(FActorTargetingOwnerContext& Context) override;

protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
    void ModifyTargetingContext();

    UFUNCTION(BlueprintCallable)
    void PerformTargetingQueue();

    UFUNCTION(BlueprintCallable)
    void ClearConfirmedActors();

private:
    bool MakeTargetData(FGameplayAbilityTargetDataHandle& DataHandle);

private:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = "true"))
    FActorTargetingOwnerContext_MeleeWeapon TargetingOwnerContext;
    // ~End ActorTargeting
#pragma endregion ActorTargeting
};
