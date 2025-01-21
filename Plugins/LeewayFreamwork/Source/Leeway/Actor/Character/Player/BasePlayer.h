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
#pragma region Locomotion
	

#pragma endregion Locomotion
};
