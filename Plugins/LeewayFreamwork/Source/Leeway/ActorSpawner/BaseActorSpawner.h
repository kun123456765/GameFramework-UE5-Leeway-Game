//--------------------
// kun 2025.02.05
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "BaseActorSpawner.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class ABaseActorSpawner : public AActor
{
	GENERATED_BODY()

public:
    ABaseActorSpawner(const FObjectInitializer& ObjectInitializer);

public:
    virtual void PostInitializeComponents() override;
    virtual void Destroyed() override;
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Leeway, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USceneComponent> RootSceneComp;

    UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = Leeway)
    TSubclassOf<AActor> ActorClassToSpawn;

    UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = Leeway)
    FTransform SpawnOffsetTransform;

private:
    FTransform ActorOffsetTransform;

#if WITH_EDITORONLY_DATA
    virtual void OnConstruction(const FTransform& Transform) override;
    void SetPreviewActorHiddenInEditor(AActor* Actor);
    UPROPERTY(VisibleAnywhere, Transient)
    TObjectPtr<AActor> PreviewActor;
#endif
};
