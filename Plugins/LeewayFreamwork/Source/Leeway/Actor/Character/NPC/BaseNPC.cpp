//--------------------
// kun 2024.12.22
//--------------------

#include "BaseNPC.h"
#include "Leeway/GameplayAbilities/GameAbilitySystemComponent.h"

ABaseNPC::ABaseNPC(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    AbilitySystemComponenct = CreateDefaultSubobject<UGameAbilitySystemComponent>(UBaseAbilitySystemComponent::AbilitySystemComponentName);
}

void ABaseNPC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

void ABaseNPC::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    ChangeASC(AbilitySystemComponenct);
}

void ABaseNPC::BeginPlay()
{
    Super::BeginPlay();
    UE_LOGD2(TEXT("WorldType=%s"), LexToString(GetWorld()->WorldType));
}

void ABaseNPC::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
