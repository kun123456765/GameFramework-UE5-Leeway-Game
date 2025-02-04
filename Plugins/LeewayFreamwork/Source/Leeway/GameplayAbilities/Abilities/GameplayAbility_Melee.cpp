//--------------------
// kun 2025.01.23
//--------------------

#include "GameplayAbility_Melee.h"
#include "MotionWarpingComponent.h"

void UGameplayAbility_Melee::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    FTimerManagerTimerParameters TimerParams;
    TimerParams.bMaxOncePerFrame = true;
    TimerParams.bLoop = true;
    GetWorld()->GetTimerManager().SetTimer(TickTimer, FTimerDelegate::CreateUObject(this, &ThisClass::OnTimer_Tick), 1.f / 120.f, TimerParams);
    Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGameplayAbility_Melee::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
    auto* AvatarActor = GetAvatarActorFromActorInfo();
    if (UMotionWarpingComponent* MWComp = AvatarActor->GetComponentByClass<UMotionWarpingComponent>())
    {
        MWComp->RemoveWarpTarget(TEXT("MoveTo"));
        MWComp->RemoveWarpTarget(TEXT("FaceTo"));
    }
    MotionWarpingTargetActor.Reset();
    GetWorld()->GetTimerManager().ClearTimer(TickTimer);
    Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UGameplayAbility_Melee::OnTakeDamage(const FGameplayTag& TriggerTag, const FGameplayAbilityTargetDataHandle& TargetData)
{
    auto* ASC = GetAbilitySystemComponentFromActorInfo_Checked();
    FGameplayEventData Payload;
    Payload.EventTag = TriggerTag;
    Payload.TargetData = TargetData;
    FScopedPredictionWindow NewScopedWindow(ASC, true);
    ASC->HandleGameplayEvent(TriggerTag, &Payload);
}

void UGameplayAbility_Melee::OnTimer_Tick()
{
    UpdateWarpTarget();
}

/*
* TArray<FOverlapResult> Overlaps; 
* �����������飬��һ��Actor X, �ҳ�����X��ǰ��n���ھ�������Ľ������������
*/
FOverlapResult* FindClosestActorInFront(const TArray<FOverlapResult>& Overlaps, AActor* X, float DegreeThreshold)
{
    if (!X || Overlaps.Num() == 0)
    {
        return nullptr;
    }

    float HalfAngle = DegreeThreshold * 0.5f;

    // ��ȡ Actor X ��λ�ú���ǰ������
    const FVector XLocation = X->GetActorLocation();
    const FVector XForward = X->GetActorForwardVector();

    // Ԥ����Ƕȵ�����ֵ���Ż����㣩
    const float CosTheta = FMath::Cos(FMath::DegreesToRadians(HalfAngle));

    FOverlapResult* ClosestResult = nullptr;
    float MinDistanceSquared = FLT_MAX; // ��¼��С�����ƽ�������⿪���ţ�

    // �������� Overlap ���
    for (const FOverlapResult& Result : Overlaps)
    {
        // ��ȡĿ�� Actor
        AActor* TargetActor = Result.GetActor();
        if (!IsValid(TargetActor) || TargetActor == X)
        {
            continue; // ������Ч Actor ������
        }

        // ����Ŀ��λ�õ� X ������
        const FVector TargetLocation = TargetActor->GetActorLocation();
        const FVector DirToTarget = TargetLocation - XLocation;
        if (DirToTarget.IsNearlyZero(1e-3f))
        {
            continue; // ����λ����ȫ�غϵ����
        }

        // ��׼������������������
        const FVector NormalizedDir = DirToTarget.GetSafeNormal();
        const float DotProduct = FVector::DotProduct(XForward, NormalizedDir);

        // ����Ƿ��ڽǶ���ֵ��
        if (DotProduct >= CosTheta)
        {
            // �������ƽ�����Ż����ܣ�
            const float DistanceSquared = DirToTarget.SizeSquared();

            // ����������
            if (DistanceSquared < MinDistanceSquared)
            {
                MinDistanceSquared = DistanceSquared;
                ClosestResult = const_cast<FOverlapResult*>(&Result); // ǿ��ȥ const���������
            }
        }
    }

    return ClosestResult;
}

void UGameplayAbility_Melee::UpdateWarpTarget()
{
    auto* AvatarActor = GetAvatarActorFromActorInfo();
    if (UMotionWarpingComponent* MWComp = AvatarActor->GetComponentByClass<UMotionWarpingComponent>())
    {
        if (!MotionWarpingTargetActor.IsValid())
        {
            FCollisionObjectQueryParams QueryParams(FCollisionObjectQueryParams::AllDynamicObjects);
            QueryParams.AddObjectTypesToQuery(ECC_Pawn);
            QueryParams.AddObjectTypesToQuery(ECC_PhysicsBody);
            TArray<FOverlapResult> Overlaps;
            FVector OverlapCenter = GetAvatarActorFromActorInfo()->GetActorLocation();
            FCollisionShape Shape = FCollisionShape::MakeSphere(AutoTargetingParams.Radius);
            bool bHitted = GetWorld()->OverlapMultiByObjectType(Overlaps, OverlapCenter, FQuat::Identity, QueryParams, Shape);
            if (bHitted)
            {
                if (FOverlapResult* Closest = FindClosestActorInFront(Overlaps, AvatarActor, 350))
                {
                    MotionWarpingTargetActor = Closest->GetActor();
                    NSLeeway::DrawDebugSection(1, GetWorld(), OverlapCenter, Shape.GetSphereRadius(), 350, AvatarActor->GetActorQuat(), FColor::Yellow, false, 3);
                }
            }
        }

        if (MotionWarpingTargetActor.IsValid())
        {
            FVector AvatarActorLoc = AvatarActor->GetActorLocation();
            FVector TargetActorLoc = MotionWarpingTargetActor->GetActorLocation();
            FVector FaceVector = TargetActorLoc - AvatarActorLoc;
            FVector FaceDir2D = FaceVector.GetSafeNormal2D();
            FVector MoveTo = TargetActorLoc - FaceDir2D * 135.f;
            FQuat FaceTo = FQuat::FindBetweenNormals(FVector::ForwardVector, FaceDir2D);
            MWComp->AddOrUpdateWarpTargetFromTransform(TEXT("MoveTo"), FTransform(AvatarActor->GetActorRotation(), MoveTo));
            MWComp->AddOrUpdateWarpTargetFromTransform(TEXT("FaceTo"), FTransform(FaceTo));
            
            NSLeeway::DrawDebugDirectionalArrow(1, GetWorld(), AvatarActorLoc, MoveTo, 15, FColor::Green, false, 3);
            NSLeeway::DrawDebugPoint(1, GetWorld(), TargetActorLoc, 5, FColor::Red, false, 3);
        }
        else
        {
            MWComp->RemoveWarpTarget(TEXT("MoveTo"));
            MWComp->RemoveWarpTarget(TEXT("FaceTo"));
        }
    }
}
