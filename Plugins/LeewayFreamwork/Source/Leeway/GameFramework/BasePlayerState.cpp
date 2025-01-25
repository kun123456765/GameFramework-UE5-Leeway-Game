//--------------------
// kun 2024.12.22
//--------------------

#include "BasePlayerState.h"
#include "Leeway/GameplayAbilities/BaseAbilitySystemComponent.h"

ABasePlayerState::ABasePlayerState(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	CreateAbilitySystemComponent(ASC);

	// todo kun 2025.01.25
	// ASC��Ҫ��Ƶ�������ô��һ����?
	NetUpdateFrequency = 100.0f;
}

inline UAbilitySystemComponent* ABasePlayerState::GetAbilitySystemComponent() const
{
	return ASC;
}

void ABasePlayerState::CreateAbilitySystemComponent(TObjectPtr<UGameAbilitySystemComponent>& Comp)
{
	Comp = CreateDefaultSubobject<UGameAbilitySystemComponent>(TEXT("GASComponent"));
}
