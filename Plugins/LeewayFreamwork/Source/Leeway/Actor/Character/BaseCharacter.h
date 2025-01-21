//--------------------
// kun 2024.12.22
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBaseCharacter, Log, All);

UCLASS(MinimalAPI, Blueprintable)
class ABaseCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()
public:
	virtual void PostInitializeComponents() override;

private:
	void CreatePartialMeshComponent(TObjectPtr<USkeletalMeshComponent>& Comp, FName Name, FTransform Trans = FTransform::Identity);

protected:
	UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> MainSkeletalMesh;

	UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Head;

	UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Hair;

	UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Torso;

	UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Legs;

	UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Hands;

	UPROPERTY(Category = BaseCharacter, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Feet;
};
