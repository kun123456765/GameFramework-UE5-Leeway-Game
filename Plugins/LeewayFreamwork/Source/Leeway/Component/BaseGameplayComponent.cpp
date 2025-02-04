//--------------------
// kun 2025.01.17
//--------------------

#include "BaseGameplayComponent.h"

UBaseGameplayComponent::UBaseGameplayComponent(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    //SetIsReplicatedByDefault(true);
}

void UBaseGameplayComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UBaseGameplayComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}
