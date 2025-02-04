//--------------------
// kun 2024.12.22
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerState.h"
#include "Components/SkeletalMeshComponent.h"
#include "PhysicsEngine/PhysicsAsset.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "Leeway/Animation/AnimLayers/BaseAnimLayers.h"
#include "Leeway/Animation/AnimDataAsset/LocomotionAnimDataAsset.h"
#include "Leeway/GameplayAbilities/LWAbilitySystemDataAsset.h"
#include "BaseCharacter.generated.h"

class UBaseAbilitySystemComponent;
class UBaseCharacterMovementComponent;


DECLARE_LOG_CATEGORY_EXTERN(LogBaseCharacter, Log, All);

UCLASS(MinimalAPI, Blueprintable)
class ABaseCharacter : public ACharacter
    , public IAbilitySystemInterface
{
    GENERATED_UCLASS_BODY()

public:
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    virtual void PostInitializeComponents() override;
    virtual void OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState) override;
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    //----------------------------------------
    // ASC Interface
    //----------------------------------------
public:
    virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
    virtual void OnPlayerStateChangedImpl(APlayerState* NewPlayerState, APlayerState* OldPlayerState);
    
protected:
    void ChangeASC(UBaseAbilitySystemComponent* NewASC);

    UFUNCTION(BlueprintCallable)
    virtual void PreInitASC();
    UFUNCTION(BlueprintCallable)
    virtual void PostInitASC();
    UFUNCTION(BlueprintCallable)
    virtual void PreUninitASC();
    UFUNCTION(BlueprintCallable)
    virtual void PostUninitASC();

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Leeway|ASC", meta = (AllowPrivateAccess = "true"))
    TWeakObjectPtr<UBaseAbilitySystemComponent> ASC;

private:
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Leeway|ASC", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<ULWAbilitySystemDataAsset> DA_AbilitySystem;

    TWeakObjectPtr<APlayerState> LastPlayerState;


#pragma region Locomotion
    //----------------------------------------
    // Locomotion
    //----------------------------------------
public:
    UFUNCTION(BlueprintCallable, meta = (DeprecatedFunction))
    void ChangeStance(const FGameplayTag& InStanceTag);

    UFUNCTION(BlueprintGetter)
    const FGameplayTag& GetStance() const { return Stance; }

    UFUNCTION(BlueprintSetter)
    void SetStance(const FGameplayTag& Value);

protected:
    UFUNCTION()
    void OnRep_Stance(FGameplayTag PrevValue) { OnStanceChanged(PrevValue); }
    void OnStanceChanged(FGameplayTag PrevValue = FGameplayTag::EmptyTag);

protected:
    UFUNCTION()
    void OnAnimInitialized();

private:
    UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Leeway|Locomotion", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<ULocomotionAnimDataAsset> DA_LocomotionAnim;

    UPROPERTY(ReplicatedUsing = OnRep_Stance, EditDefaultsOnly, Category = "Leeway|Locomotion", BlueprintGetter = GetStance, BlueprintSetter = SetStance)
    FGameplayTag Stance;
#pragma endregion Locomotion

#pragma region Ragdoll
    //----------------------------------------
    // Ragdoll
    //----------------------------------------
public:
    UFUNCTION(BlueprintGetter)
    bool GetRagdollEnable() const { return bRagdollEnabled; }
    UFUNCTION(BlueprintSetter)
    void SetRagdollEnable(bool Value);

protected:
    UFUNCTION()
    void OnRep_RagdollEnabled(bool bPrevValue) { OnRagdollChanged(bPrevValue); }
    UFUNCTION(BlueprintNativeEvent)
    void OnRagdollChanged(bool bPrevValue = false);

    UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UBaseCharacterMovementComponent> BaseCharacterMovement;

protected:
    UPROPERTY(ReplicatedUsing = OnRep_RagdollEnabled, BlueprintReadWrite, EditDefaultsOnly, Category = "Leeway|Ragdoll", BlueprintGetter = GetRagdollEnable, BlueprintSetter = SetRagdollEnable)
    uint8 bRagdollEnabled : 1;

    struct FRagdollOriginState
    {
        FTransform MeshTransform;
        ECollisionEnabled::Type MeshCollisionEnabled;

        EMovementMode MovementMode;
        uint8 CustomMovementMode;

        ECollisionEnabled::Type CapsuleCollisionEnabled;
    } RagdollOriginState;

#pragma endregion Ragdoll
    //----------------------------------------
    // Mesh Composite
    //----------------------------------------
private:
    void CreatePartialMeshComponent(TObjectPtr<USkeletalMeshComponent>& Comp, FName Name, FTransform Trans = FTransform::Identity);

protected:
    UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USkeletalMeshComponent> MainSkeletalMesh;

    //UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    //TObjectPtr<USkeletalMeshComponent> Head;

    //UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    //TObjectPtr<USkeletalMeshComponent> Hair;

    //UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    //TObjectPtr<USkeletalMeshComponent> Torso;

    //UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    //TObjectPtr<USkeletalMeshComponent> Legs;

    //UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    //TObjectPtr<USkeletalMeshComponent> Hands;

    //UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
    //TObjectPtr<USkeletalMeshComponent> Feet;

#pragma region Combat
private:
    UFUNCTION(BlueprintCallable)
    void DebugDrawBones(FLinearColor Color) const;
    UFUNCTION(BlueprintCallable)
    void DebugDrawBoneByName(FName BoneName, FLinearColor Color) const;
    UFUNCTION(BlueprintCallable)
    void DebugDrawBoneByIndex(int BoneIndex, FLinearColor Color) const;
#pragma endregion Combat
};
