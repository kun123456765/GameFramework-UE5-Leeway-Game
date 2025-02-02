//--------------------
// kun 2025.01.31
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Engine/DataAsset.h"
#include "LWAbilitySystemDataAsset.generated.h"


USTRUCT(BlueprintType)
struct FGrantedAttriSetSet
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	TArray<TSubclassOf<UAttributeSet>> AttriSets;
};


USTRUCT(BlueprintType)
struct FGrantedAbility
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	TSubclassOf<UGameplayAbility> AbilityClass;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	int32 Level = 1;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	bool bActivateOnGiveAbility = false;
};

USTRUCT(BlueprintType)
struct FGrantedAbilitySet
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	TArray<FGrantedAbility> Abilities;
};

USTRUCT(BlueprintType)
struct FGrantedSet
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	FGrantedAbilitySet AbilitySet;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	FGrantedAttriSetSet AttriSetSet;
};

UCLASS(BlueprintType)
class ULWAbilitySystemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	FGrantedSet GrantedSet;
};

USTRUCT(BlueprintType)
struct FGrantedHandleSet
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	TArray<FGameplayAbilitySpecHandle> Abilities;

	UPROPERTY(BlueprintReadWrite, EditAnyWhere)
	TArray<FActiveGameplayEffectHandle> Effects;
};