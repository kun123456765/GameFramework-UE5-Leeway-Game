//--------------------
// kun 2025.01.23
//--------------------

#include "GameplayAbility_Attack.h"

UGameplayAbility_Attack::UGameplayAbility_Attack(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    if (HasAnyFlags(RF_ClassDefaultObject))
    {
        ReplicationPolicy = EGameplayAbilityReplicationPolicy::ReplicateYes;
        InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
        NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
    }
}
