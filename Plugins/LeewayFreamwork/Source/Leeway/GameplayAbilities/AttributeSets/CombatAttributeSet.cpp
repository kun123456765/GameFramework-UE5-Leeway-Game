//--------------------
// kun 2025.01.23
//--------------------

#include "CombatAttributeSet.h"
#include "GameplayEffectExtension.h"

bool UCombatAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	return true;
}

void UCombatAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, Health, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UCombatAttributeSet, MaxHealth, COND_None, REPNOTIFY_OnChanged);
}

void UCombatAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
	AActor* Instigator = EffectContext.GetOriginalInstigator();
	AActor* Causer = EffectContext.GetEffectCauser();

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Clamp and fall into out of health handling below
		//SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		//SetMaxHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
	}
}

void UCombatAttributeSet::OnRep_Health(const FGameplayAttributeData& PrevValue)
{
}

void UCombatAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& PrevValue)
{
}

void UCombatAttributeSet::OnRep_Shield(const FGameplayAttributeData& PrevValue)
{
}

void UCombatAttributeSet::OnRep_Damage(const FGameplayAttributeData& PrevValue)
{
}

void UCombatAttributeSet::OnRep_Healing(const FGameplayAttributeData& PrevValue)
{
}

void UCombatAttributeSet::OnRep_ReplenishShield(const FGameplayAttributeData& PrevValue)
{
}
