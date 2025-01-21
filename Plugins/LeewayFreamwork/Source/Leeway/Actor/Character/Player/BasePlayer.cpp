//--------------------
// kun 2024.12.22
//--------------------

#include "BasePlayer.h"
#include "Leeway/Component/BaseCharacterMovementComponent.h"

ABasePlayer::ABasePlayer(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer.SetDefaultSubobjectClass<UBaseCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
}
