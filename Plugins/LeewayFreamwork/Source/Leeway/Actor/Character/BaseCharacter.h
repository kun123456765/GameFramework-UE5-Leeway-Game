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
	virtual void BeginPlay() override;

	//----------------------------------------
	// ASC Interface
	//----------------------------------------
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	virtual void OnPlayerStateChanged(APlayerState* NewPlayerState, APlayerState* OldPlayerState) override;
	
	virtual void OnPlayerStateChangedImpl(APlayerState* NewPlayerState, APlayerState* OldPlayerState);

	TWeakObjectPtr<APlayerState> LastPlayerState;


#pragma region Locomotion
	//----------------------------------------
	// Locomotion
	//----------------------------------------
public:
	UFUNCTION(BlueprintCallable)
	void ChangeStance(const FGameplayTag& InStanceTag);

public:
	UFUNCTION(BlueprintGetter)
	const FGameplayTag& GetStance() const;

	UFUNCTION(BlueprintSetter)
	void SetStance(const FGameplayTag& Value);

protected:
	UFUNCTION()
	void OnRep_Stance(FGameplayTag PrevStanceTag);
	void OnStanceChanged(FGameplayTag PrevStanceTag = FGameplayTag::EmptyTag);

private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Leeway/Locomotion", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<ULocomotionAnimDataAsset> DA_LocomotionAnim;

	UPROPERTY(ReplicatedUsing = OnRep_Stance, EditDefaultsOnly, Category = "Leeway/Locomotion")
	FGameplayTag Stance;

protected:
	UFUNCTION()
	void OnAnimInitialized();
#pragma endregion Locomotion

	//----------------------------------------
	// Mesh Composite
	//----------------------------------------
private:
	void CreatePartialMeshComponent(TObjectPtr<USkeletalMeshComponent>& Comp, FName Name, FTransform Trans = FTransform::Identity);

protected:
	UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> MainSkeletalMesh;

	//UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<USkeletalMeshComponent> Head;

	//UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<USkeletalMeshComponent> Hair;

	//UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<USkeletalMeshComponent> Torso;

	//UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<USkeletalMeshComponent> Legs;

	//UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<USkeletalMeshComponent> Hands;

	//UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<USkeletalMeshComponent> Feet;

	UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TWeakObjectPtr<UBaseAbilitySystemComponent> ASC;

	UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBaseCharacterMovementComponent> BaseCharacterMovement;

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
