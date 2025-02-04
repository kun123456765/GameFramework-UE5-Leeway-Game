//--------------------
// kun 2025.02.02
//--------------------

#include "LWGameplayTags.h"

#define LW_DEFINE_GAMEPLAY_TAG_WITH_COMMENT(Var, Tag, DevComment) Var(UE_PLUGIN_NAME, UE_MODULE_NAME, Tag, DevComment, ENativeGameplayTagToken::PRIVATE_USE_MACRO_INSTEAD)
#define LW_DEFINE_GAMEPLAY_TAG(Scope, Var) LW_DEFINE_GAMEPLAY_TAG_WITH_COMMENT(Var, "LW."#Scope"."#Var, TEXT(""))

FLWGameplayTags FLWGameplayTags::Singleton;

FLWGameplayTags::FGALabel::FGALabel()
    : LW_DEFINE_GAMEPLAY_TAG(GALabel, IgnoreToDeath)
    , LW_DEFINE_GAMEPLAY_TAG(GALabel, IgnoreToUninitial)
{
}

FLWGameplayTags::FSetByCaller::FSetByCaller()
    : LW_DEFINE_GAMEPLAY_TAG(SetByCaller, Healing)
    , LW_DEFINE_GAMEPLAY_TAG(SetByCaller, Replenish)
    , LW_DEFINE_GAMEPLAY_TAG(SetByCaller, Damage)
{
}

FLWGameplayTags::FGameEvent::FGameEvent()
    : LW_DEFINE_GAMEPLAY_TAG(GameEvent, Death)
    , LW_DEFINE_GAMEPLAY_TAG(GameEvent, Revive)
{
}
