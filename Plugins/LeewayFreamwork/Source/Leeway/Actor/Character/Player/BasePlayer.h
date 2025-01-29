//--------------------
// kun 2024.12.22
//--------------------

#pragma once

#include "CoreMinimal.h"
#include "Leeway/Actor/Character/BaseCharacter.h"
#include "BasePlayer.generated.h"

UCLASS(MinimalAPI, Blueprintable)
class ABasePlayer : public ABaseCharacter
{
	GENERATED_BODY()
public:
	ABasePlayer(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

	virtual void Tick(float DeltaSeconds) override;

#pragma region Locomotion
	
private:
	UFUNCTION(BlueprintCallable)
	void DebugDrawBones(FLinearColor Color) const;
	UFUNCTION(BlueprintCallable)
	void DebugDrawBoneByName(FName BoneName, FLinearColor Color) const;
	UFUNCTION(BlueprintCallable)
	void DebugDrawBoneByIndex(int BoneIndex, FLinearColor Color) const;

#pragma endregion Locomotion
};
