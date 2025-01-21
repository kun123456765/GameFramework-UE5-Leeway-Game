//--------------------
// kun 2024.12.22
//--------------------

#include "BaseGameMode.h"
#include "UObject/ConstructorHelpers.h"

ABaseGameMode::ABaseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/LeewayFreamwork/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
