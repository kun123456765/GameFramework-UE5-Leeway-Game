//--------------------
// kun 2025.01.04
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "BaseGameplayEffect.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class UBaseGameplayEffect : public UGameplayEffect
{
	GENERATED_BODY()

#if false
public:
	virtual void GetBlockedAbilityTags(FGameplayTagContainer& OutTagContainer) const;
	virtual void PostInitProperties() override;
	virtual void PostLoad() override;
	virtual void OnGameplayEffectChanged();
#if WITH_EDITOR
	virtual void PostCDOCompiled(const FPostCDOCompiledContext& Context) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
protected:
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
#endif
};
