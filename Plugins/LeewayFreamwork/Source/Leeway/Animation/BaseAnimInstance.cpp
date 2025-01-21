//--------------------
// kun 2025.01.17
//--------------------


#include "BaseAnimInstance.h"

//#include "AnimCharacterMovementLibrary.h"
//#include "AnimDistanceMatchingLibrary.h"
//#include "AnimExecutionContextLibrary.h"
//#include "KismetAnimationLibrary.h"
//#include "SequenceEvaluatorLibrary.h"
//#include "SequencePlayerLibrary.h"
//#include "Animation/AnimInstanceProxy.h"
//#include "Components/CapsuleComponent.h"
//#include "GameFramework/Character.h"

UBaseAnimInstance::UBaseAnimInstance()
{
	
}

void UBaseAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	UpdateAnimGraphContext(DeltaSeconds);
}

const TSharedRef<FAnimGraphContext> UBaseAnimInstance::GetAnimGraphContext() const
{
	return MakeShared<FAnimGraphContext>(AnimGraphContext);
}

void UBaseAnimInstance::UpdateAnimGraphContext(float DeltaSeconds)
{
}
