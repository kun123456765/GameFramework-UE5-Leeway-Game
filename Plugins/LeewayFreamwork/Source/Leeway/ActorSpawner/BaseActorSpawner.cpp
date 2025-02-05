//--------------------
// kun 2025.02.05
//--------------------

#include "BaseActorSpawner.h"
#include "Leeway/Actor/Character/BaseCharacter.h"

ABaseActorSpawner::ABaseActorSpawner(const FObjectInitializer& ObjectInitializer)
    :Super(ObjectInitializer)
{
    SetReplicates(false);
    NetDormancy = ENetDormancy::DORM_DormantAll;
    bNetLoadOnClient = false;

    RootSceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComp"));
    SetRootComponent(RootSceneComp);
}

void ABaseActorSpawner::PostInitializeComponents()
{
    Super::PostInitializeComponents();
}

void ABaseActorSpawner::Destroyed()
{
#if WITH_EDITORONLY_DATA
    if (PreviewActor)
    {
        PreviewActor->Destroy(true);
        PreviewActor = nullptr;
    }
#endif

    Super::Destroyed();
}

void ABaseActorSpawner::BeginPlay()
{
    Super::BeginPlay();
    if (HasAuthority())
    {
        FTransform WorldTrans = GetActorTransform() * ActorOffsetTransform;
        GetWorld()->SpawnActor(ActorClassToSpawn, &WorldTrans);
    }

    //todo kun 2025.02.05
    // 需要发到客户端来看;
    DrawDebugPoint(GetWorld(), (GetActorTransform() * ActorOffsetTransform).GetLocation(), 50, FColor::Green, false, 30);

#if WITH_EDITORONLY_DATA
    if (PreviewActor)
    {
        PreviewActor->Destroy(true);
        PreviewActor = nullptr;
    }
#endif
}

void ABaseActorSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

#if WITH_EDITORONLY_DATA
void ABaseActorSpawner::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    if(!IsValid(ActorClassToSpawn) 
        || IsValid(PreviewActor) && PreviewActor->GetClass() != ActorClassToSpawn.Get())
    {
        // 销毁PreviewActor;
        if (IsValid(PreviewActor))
        {
            PreviewActor->Destroy();
            PreviewActor = nullptr;
        }
    }

    if (IsValid(ActorClassToSpawn))
    {
        // 创建PreviewActor;
        if (!IsValid(PreviewActor))
        {
            FActorSpawnParameters SpawnParamters;
            SpawnParamters.bTemporaryEditorActor = true;
            SpawnParamters.ObjectFlags = (EObjectFlags)(RF_Transient | RF_DuplicateTransient | RF_NonPIEDuplicateTransient | RF_TextExportTransient);
            PreviewActor = GetWorld()->SpawnActor<AActor>(ActorClassToSpawn, SpawnParamters);
            PreviewActor->SetActorEnableCollision(false);
            PreviewActor->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
            SetPreviewActorHiddenInEditor(PreviewActor);
        }
    }

    if (IsValid(PreviewActor))
    {
        // 调整PreviewActor位置;
        FTransform PreviewTransform(FTransform::Identity);
        const AActor* ActorCDO = ActorClassToSpawn->GetDefaultObject<AActor>();
        FVector RelativeLocation;
        if (auto* SKM = ActorCDO->FindComponentByClass<USkeletalMeshComponent>())
        {
            if (SKM->LeaderPoseComponent.IsValid())
            {
                RelativeLocation = SKM->LeaderPoseComponent->GetRelativeLocation();
            }
            else
            {
                RelativeLocation = SKM->GetRelativeLocation();
            }
        }
        else if (auto* SM = ActorCDO->FindComponentByClass<UStaticMeshComponent>())
        {
            RelativeLocation = SM->GetRelativeLocation();
        }
        RelativeLocation.Z = -RelativeLocation.Z;
        PreviewTransform.SetLocation(RelativeLocation);
        ActorOffsetTransform = PreviewTransform;
        PreviewActor->SetActorRelativeTransform(PreviewTransform);
    }
}

void ABaseActorSpawner::SetPreviewActorHiddenInEditor(AActor* Actor)
{
    if (auto* LWActor = Cast<ABaseCharacter>(PreviewActor))
    {
        // Hidden in World Outliner;
        LWActor->bListedInSceneOutliner = false;
        LWActor->bActorLabelEditable = false;
        // Hidden Anywhere;
        //LWActor->bEditable = false;
    }
}
#endif
