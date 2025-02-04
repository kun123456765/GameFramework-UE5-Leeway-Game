//--------------------
// kun 2025.01.17
//--------------------

#include "CharacterDeathComponent.h"

UCharacterDeathComponent::UCharacterDeathComponent(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    //SetIsReplicatedByDefault(true);
}

void UCharacterDeathComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UCharacterDeathComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
