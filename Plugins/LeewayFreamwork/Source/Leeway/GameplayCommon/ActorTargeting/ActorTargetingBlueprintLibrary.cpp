//--------------------
// kun 2025.01.27
//--------------------

#include "ActorTargetingBlueprintLibrary.h"
#include "ActorTargetingTypes.h"

struct FActorTargetingContextDeleter
{
    FORCEINLINE void operator()(FActorTargetingContext* Object) const
    {
        check(Object);
        UScriptStruct* ScriptStruct = Object->GetScriptStruct();
        check(ScriptStruct);
        ScriptStruct->DestroyStruct(Object);
        FMemory::Free(Object);
    }
};

DEFINE_FUNCTION(UActorTargetingBlueprintLibrary::execCreateActorTargetingContext)
{
    P_GET_STRUCT_REF(FActorTargetingContextSharedPtr, ContextHandle);

    Stack.MostRecentPropertyAddress = nullptr;
    Stack.MostRecentPropertyContainer = nullptr;
    Stack.StepCompiledIn<FStructProperty>(NULL);
    void* PropertyAddress = Stack.MostRecentPropertyAddress;
    FStructProperty* StructProp = CastField<FStructProperty>(Stack.MostRecentProperty);

    P_FINISH;

    if (!PropertyAddress)
        return;

    if (!StructProp || StructProp->Struct)
        return;

    if (!StructProp->Struct->IsChildOf(FActorTargetingContext::StaticStruct()))
        return;

    FActorTargetingContext* NewStructObj = reinterpret_cast<FActorTargetingContext*>(FMemory::Malloc(StructProp->Struct->GetStructureSize()));
    StructProp->Struct->InitializeStruct(NewStructObj);
    StructProp->Struct->CopyScriptStruct(NewStructObj, PropertyAddress);
    TSharedPtr<FActorTargetingContext> ContextPtr = TSharedPtr<FActorTargetingContext>(NewStructObj, FActorTargetingContextDeleter());
    ContextHandle.Context = ContextPtr;
}
