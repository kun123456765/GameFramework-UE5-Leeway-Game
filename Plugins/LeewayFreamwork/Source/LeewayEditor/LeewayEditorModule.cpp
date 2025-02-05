//--------------------
// kun 2024.12.27
//--------------------

#include "LeewayEditorModule.h"
#include "LevelEditorActions.h"
#include "LevelEditorViewport.h"
#include "LevelEditor.h"
#include "Leeway/ActorSpawner/BaseActorSpawner.h"

#define LOCTEXT_NAMESPACE "FLeewayEditorModule"

void FLeewayEditorModule::StartupModule()
{
    FLevelEditorModule& LevelEditor = FModuleManager::GetModuleChecked<FLevelEditorModule>("LevelEditor");
    LevelEditor.OnActorSelectionChanged().AddRaw(this, &FLeewayEditorModule::OnActorSelectionChanged);
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FLeewayEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

AActor* GetTopAttachmentActor(AActor* Actor)
{
    AActor* Current = Actor;
    while (Current && Current->GetAttachParentActor())
    {
        Current = Current->GetAttachParentActor();
    }
    return Current;
}

void FLeewayEditorModule::OnActorSelectionChanged(const TArray<UObject*>& NewSelection, bool bForceRefresh)
{
    static bool bIsUpdatingSelection = false;
    if (bIsUpdatingSelection) return;

    TArray<AActor*> FilteredActors;
    for (UObject* Obj : NewSelection)
    {
        if (AActor* Actor = Cast<AActor>(Obj))
        {
            AActor* TopActor = GetTopAttachmentActor(Actor);
            if (bool bActorSpawner = TopActor->GetClass()->IsChildOf<ABaseActorSpawner>())
            {
                FilteredActors.AddUnique(TopActor);
            }
            else
            {
                FilteredActors.Add(Actor);
            }
        }
    }

    // 避免重复处理
    bIsUpdatingSelection = true;
    {
        GEditor->SelectNone(false, true, false);
        for (AActor* Actor : FilteredActors)
        {
            GEditor->SelectActor(Actor, true, true, true);
        }
        GEditor->NoteSelectionChange();
        // (备选方案)
        //FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
        //PropertyModule.NotifyCustomizationModuleChanged(); // 强制刷新Details面板
    }
    bIsUpdatingSelection = false;
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FLeewayEditorModule, Leeway)