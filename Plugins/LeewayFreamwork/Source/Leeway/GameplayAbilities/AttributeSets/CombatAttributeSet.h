//--------------------
// kun 2025.01.23
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BaseAttributeSet.h"
#include "CombatAttributeSet.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class UCombatAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;

public:
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Shield);
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Damage);
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Healing);
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, ReplenishShield);

private:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& PrevValue);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& PrevValue);
	UFUNCTION()
	void OnRep_Shield(const FGameplayAttributeData& PrevValue);
	UFUNCTION()
	void OnRep_Damage(const FGameplayAttributeData& PrevValue);
	UFUNCTION()
	void OnRep_Healing(const FGameplayAttributeData& PrevValue);
	UFUNCTION()
	void OnRep_ReplenishShield(const FGameplayAttributeData& PrevValue);

private:
    UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Health;
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(ReplicatedUsing = OnRep_Shield, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Shield;

	UPROPERTY(ReplicatedUsing = OnRep_Damage, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Damage;

	UPROPERTY(ReplicatedUsing = OnRep_Healing, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Healing;
	
	UPROPERTY(ReplicatedUsing = OnRep_ReplenishShield, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData ReplenishShield;
};
