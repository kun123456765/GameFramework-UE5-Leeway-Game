//--------------------
// kun 2025.01.26
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "Leeway/GameplayCommon/ActorTargeting/ActorTargetingOwnerInterface.h"
#include "BaseGameplayAbilityTargetActor.generated.h"

UCLASS(MinimalAPI, Blueprintable, Abstract)
class ABaseGameplayAbilityTargetActor : public AGameplayAbilityTargetActor, public IActorTargetingOwnerInterface
{
    GENERATED_BODY()

#if false
    virtual void StartTargeting(UGameplayAbility* Ability);

    virtual bool IsConfirmTargetingAllowed();
    virtual bool ShouldProduceTargetData() const;

    virtual void ConfirmTargetingAndContinue();
    virtual void ConfirmTargeting();
    virtual void CancelTargeting();

    virtual void BindToConfirmCancelInputs();

    virtual bool OnReplicatedTargetDataReceived(FGameplayAbilityTargetDataHandle& Data) const;

    virtual bool IsNetRelevantFor(const AActor* RealViewer, const AActor* ViewTarget, const FVector& SrcLocation) const override;
#endif

public:
    UFUNCTION(BlueprintCallable)
    void BPConfirmTargeting();

public:
    virtual void StartTargeting(UGameplayAbility* InAbility) override;
    virtual void ConfirmTargeting() override;

    virtual const TArray<TWeakObjectPtr<AActor>>& GetSceneQueryIgnoreActors() const;
protected:
    virtual FActorTargetingContainer& GetActorTargetingContainer() override { return ActorTargetingContainer; }

private:
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
    FActorTargetingContainer ActorTargetingContainer;

    TArray<TWeakObjectPtr<AActor>> SceneQueryIgnoreActors;
};
