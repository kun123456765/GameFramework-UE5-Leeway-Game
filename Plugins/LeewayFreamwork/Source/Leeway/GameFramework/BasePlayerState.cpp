//--------------------
// kun 2024.12.22
//--------------------

#include "BasePlayerState.h"
#include "Leeway/GameplayAbilities/GameAbilitySystemComponent.h"

ABasePlayerState::ABasePlayerState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ASC = CreateDefaultSubobject<UGameAbilitySystemComponent>(UBaseAbilitySystemComponent::AbilitySystemComponentName);

	// todo kun 2025.01.25
	// ASC需要高频，这个怎么改一改呢?
	NetUpdateFrequency = 100.0f;
}

inline UAbilitySystemComponent* ABasePlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}


int32 ABasePlayerState::HandleGameplayEvent(FGameplayTag EventTag, FGameplayEventData Payload)
{
    return HandleGameplayEvent(EventTag, &Payload);
}

int32 ABasePlayerState::HandleGameplayEvent(const FGameplayTag& EventTag, const FGameplayEventData* Payload)
{
	return ASC->UAbilitySystemComponent::HandleGameplayEvent(EventTag, Payload);
}