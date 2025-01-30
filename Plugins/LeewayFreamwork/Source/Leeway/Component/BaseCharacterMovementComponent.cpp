//--------------------
// kun 2025.01.17
//--------------------


#include "BaseCharacterMovementComponent.h"
#include "Net/Core/PushModel/PushModel.h"
#include "Leeway/Actor/Character/BaseCharacter.h"
#include "Leeway/Animation/AnimLayers/BaseAnimLayers.h"
#include "Engine/World.h"

UBaseCharacterMovementComponent::UBaseCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    //SetIsReplicatedByDefault(true);
}

void UBaseCharacterMovementComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UBaseCharacterMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
