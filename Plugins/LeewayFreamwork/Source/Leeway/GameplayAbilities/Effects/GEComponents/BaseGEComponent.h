//--------------------
// kun 2025.01.23
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectComponent.h"
#include "BaseGEComponent.generated.h"

// note by kun 2025.01.25
/*
* GE原本是OO类，现在改成了DO类，行为全部拆出去了，拆出去的行为就变成了一个个EffectComponent。
* 
* UAssetTagsGameplayEffectComponent(DisplayName="Tags This Effect Has (Asset Tags))
* 原GE AssetTags。
* 确实不是所有GE都需要一个Tag。连这个程度都要拆出来，那原则上几乎不应该将任何行为放到GE类里去了。
* 
* UAbilitiesGameplayEffectComponent(DisplayName="Grant Gameplay Abilities")
* 受GE管理的临时GA。
* 因此有必要自己搞个武器类去添加GA吗?是不是利用GE就可以管理了?可以，但是多了一层转义，因此系统变复杂了。
* 所以应该真的是需求上是“GE作为事务源才存在的GA”这种情况才使用此功能。
* 
* UAdditionalEffectsGameplayEffectComponent(CollapseCategories, DisplayName="Apply Additional Effects")
* GE触发其他GE，并且不管了。
* 触发时机有三种：激活时/结束时(必定/按时/提前)
* 
* UBlockAbilityTagsGameplayEffectComponent(DisplayName="Block Abilities with Tags")
* 与“通过GE控制GA是否能激活的机制”有关，本质是修改ASC的BlockedAbilityTags;
* 
* UChanceToApplyGameplayEffectComponent(DisplayName="Chance To Apply This Effect")
* 有点多余的装饰性功能;
* 
* UCustomCanApplyGameplayEffectComponent(DisplayName="Custom Can Apply This Effect")
* 继承UGameplayEffectCustomApplicationRequirement即可自定义条件;
* 条件写在ASC外面还是GE里面，甚至GA流程里面，都可以，看需求吧;
* GE这个扩展结构一定程度上可以复用检查条件;
* 
* UImmunityGameplayEffectComponent
* 与“控制是否能添加上GE”有关，BlockAbitity的GE版本。本质是修改ASC的GameplayEffectApplicationQueries(这字段居然是public的)
* 
* URemoveOtherGameplayEffectComponent
* 操作ASC的ActiveGameplayEffects::RemoveActiveEffects.
* 
* UTargetTagRequirementsGameplayEffectComponent
* 获取ASC的GameplayTagCountContainer跟GE做比较，
* 
* 
* UTargetTagsGameplayEffectComponent
* 全局规范写这里,任何“ASC的OwnedGameplayTags和GE进行Tags判断时。
* 尚不清楚"全局"的范围，总不能是整个Project吧?
* 
* UGameplayEffectUIData
* GE的UIAdapter，又属于管得宽的多余设计。 
*/
UCLASS(MinimalAPI, Blueprintable, Abstract)
class UBaseGEComponent : public UGameplayEffectComponent
{
	GENERATED_BODY()

	// note by kun 2025.01.23
	// 按需继承,忘了细节就回来查;
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
