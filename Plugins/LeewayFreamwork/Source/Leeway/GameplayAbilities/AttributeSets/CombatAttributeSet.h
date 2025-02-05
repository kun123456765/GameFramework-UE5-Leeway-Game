//--------------------
// kun 2025.01.23
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BaseAttributeSet.h"
#include "CombatAttributeSet.generated.h"

USTRUCT(BlueprintType)
struct FDamageInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	float HealthDamage = 0;
	UPROPERTY(BlueprintReadWrite)
	float ShieldDamage = 0;
};

USTRUCT(BlueprintType)
struct FHealingInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	float Healing = 0;
	UPROPERTY(BlueprintReadWrite)
	float Replenish = 0;
};

USTRUCT(BlueprintType)
struct FOutOfHealthInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool bOutOfHealth = false;
	UPROPERTY(BlueprintReadWrite)
	bool bShieldBroken = false;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamgeDelegate, FDamageInfo const&, DamageInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealingDelegate, FHealingInfo const&, HealingInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOutOfHealthDelegate, FOutOfHealthInfo const&, OutOfHealthInfo);

UCLASS(MinimalAPI, Blueprintable)
class UCombatAttributeSet : public UBaseAttributeSet
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;

public:
	void Initialize(float MaxHealth);

public:
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Health);
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Shield);
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, MaxShield);
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Damage);
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Healing);
	ATTRIBUTE_ACCESSORS(UCombatAttributeSet, Replenish);

private:
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& PrevValue);
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& PrevValue);
	UFUNCTION()
	void OnRep_Shield(const FGameplayAttributeData& PrevValue);
	UFUNCTION()
	void OnRep_MaxShield(const FGameplayAttributeData& PrevValue);
	UFUNCTION()
	void OnRep_Damage(const FGameplayAttributeData& PrevValue);
	UFUNCTION()
	void OnRep_Healing(const FGameplayAttributeData& PrevValue);
	UFUNCTION()
	void OnRep_Replenish(const FGameplayAttributeData& PrevValue);

private:
    UPROPERTY(ReplicatedUsing = OnRep_Health, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Health;
	
	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxHealth;

	UPROPERTY(ReplicatedUsing = OnRep_Shield, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Shield;

	UPROPERTY(ReplicatedUsing = OnRep_MaxShield, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData MaxShield;

	UPROPERTY(ReplicatedUsing = OnRep_Damage, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Damage;

	UPROPERTY(ReplicatedUsing = OnRep_Healing, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Healing;
	
	UPROPERTY(ReplicatedUsing = OnRep_Replenish, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FGameplayAttributeData Replenish;

public:
	UPROPERTY(BlueprintAssignable)
	mutable FOnDamgeDelegate OnDamge;

	UPROPERTY(BlueprintAssignable)
	mutable FOnHealingDelegate OnHealing;

	UPROPERTY(BlueprintAssignable)
	mutable FOnOutOfHealthDelegate OnOutOfHealth;

	UPROPERTY(BlueprintReadWrite, Transient)
	float LastDamageWorldTime;

private:
	struct {
		float MaxHealth = 0;
	} BeforeChangeValues;

private:
	bool bOutOfHealth = false;
	bool bShieldBroken = false;
};
