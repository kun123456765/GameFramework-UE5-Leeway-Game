//--------------------
// kun 2025.01.17
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "BaseCharacterMovementComponent.generated.h"


UCLASS(MinimalAPI, Blueprintable)
class UBaseCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()
public:
    UBaseCharacterMovementComponent(const FObjectInitializer& ObjectInitializer);
    virtual void BeginPlay() override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
