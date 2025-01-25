//--------------------
// kun 2025.01.23
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectComponent.h"
#include "BaseGEComponent.generated.h"

// note by kun 2025.01.25
/*
* GEԭ����OO�࣬���ڸĳ���DO�࣬��Ϊȫ�����ȥ�ˣ����ȥ����Ϊ�ͱ����һ����EffectComponent��
* 
* UAssetTagsGameplayEffectComponent(DisplayName="Tags This Effect Has (Asset Tags))
* ԭGE AssetTags��
* ȷʵ��������GE����Ҫһ��Tag��������̶ȶ�Ҫ���������ԭ���ϼ�����Ӧ�ý��κ���Ϊ�ŵ�GE����ȥ�ˡ�
* 
* UAbilitiesGameplayEffectComponent(DisplayName="Grant Gameplay Abilities")
* ��GE�������ʱGA��
* ����б�Ҫ�Լ����������ȥ���GA��?�ǲ�������GE�Ϳ��Թ�����?���ԣ����Ƕ���һ��ת�壬���ϵͳ�临���ˡ�
* ����Ӧ��������������ǡ�GE��Ϊ����Դ�Ŵ��ڵ�GA�����������ʹ�ô˹��ܡ�
* 
* UAdditionalEffectsGameplayEffectComponent(CollapseCategories, DisplayName="Apply Additional Effects")
* GE��������GE�����Ҳ����ˡ�
* ����ʱ�������֣�����ʱ/����ʱ(�ض�/��ʱ/��ǰ)
* 
* UBlockAbilityTagsGameplayEffectComponent(DisplayName="Block Abilities with Tags")
* �롰ͨ��GE����GA�Ƿ��ܼ���Ļ��ơ��йأ��������޸�ASC��BlockedAbilityTags;
* 
* UChanceToApplyGameplayEffectComponent(DisplayName="Chance To Apply This Effect")
* �е�����װ���Թ���;
* 
* UCustomCanApplyGameplayEffectComponent(DisplayName="Custom Can Apply This Effect")
* �̳�UGameplayEffectCustomApplicationRequirement�����Զ�������;
* ����д��ASC���滹��GE���棬����GA�������棬�����ԣ��������;
* GE�����չ�ṹһ���̶��Ͽ��Ը��ü������;
* 
* UImmunityGameplayEffectComponent
* �롰�����Ƿ��������GE���йأ�BlockAbitity��GE�汾���������޸�ASC��GameplayEffectApplicationQueries(���ֶξ�Ȼ��public��)
* 
* URemoveOtherGameplayEffectComponent
* ����ASC��ActiveGameplayEffects::RemoveActiveEffects.
* 
* UTargetTagRequirementsGameplayEffectComponent
* ��ȡASC��GameplayTagCountContainer��GE���Ƚϣ�
* 
* 
* UTargetTagsGameplayEffectComponent
* ȫ�ֹ淶д����,�κΡ�ASC��OwnedGameplayTags��GE����Tags�ж�ʱ��
* �в����"ȫ��"�ķ�Χ���ܲ���������Project��?
* 
* UGameplayEffectUIData
* GE��UIAdapter�������ڹܵÿ�Ķ�����ơ� 
*/
UCLASS(MinimalAPI, Blueprintable, Abstract)
class UBaseGEComponent : public UGameplayEffectComponent
{
	GENERATED_BODY()

	// note by kun 2025.01.23
	// ����̳�,����ϸ�ھͻ�����;
#if false
public:
	virtual bool CanGameplayEffectApply(const FActiveGameplayEffectsContainer& ActiveGEContainer, const FGameplayEffectSpec& GESpec) const { return true; }
	virtual bool OnActiveGameplayEffectAdded(FActiveGameplayEffectsContainer& ActiveGEContainer, FActiveGameplayEffect& ActiveGE) const { return true; }
	virtual void OnGameplayEffectExecuted(FActiveGameplayEffectsContainer& ActiveGEContainer, FGameplayEffectSpec& GESpec, FPredictionKey& PredictionKey) const {}
	virtual void OnGameplayEffectApplied(FActiveGameplayEffectsContainer& ActiveGEContainer, FGameplayEffectSpec& GESpec, FPredictionKey& PredictionKey) const {}
	virtual void OnGameplayEffectChanged() {};
	virtual void OnGameplayEffectChanged() const {};
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(class FDataValidationContext& Context) const override;
#endif
#endif
};
