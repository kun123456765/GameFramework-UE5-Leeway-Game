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
* 给定上述数组，和一个Actor X, 找出中在X正前方n度内距离最近的结果，给出代码
*/
FOverlapResult* FindClosestActorInFront(const TArray<FOverlapResult>& Overlaps, AActor* X, float DegreeThreshold)
{
    if (!X || Overlaps.Num() == 0)
    {
        return nullptr;
    }

    float HalfAngle = DegreeThreshold * 0.5f;

    // 获取 Actor X 的位置和正前方向量
    const FVector XLocation = X->GetActorLocation();
    const FVector XForward = X->GetActorForwardVector();

    // 预计算角度的余弦值（优化计算）
    const float CosTheta = FMath::Cos(FMath::DegreesToRadians(HalfAngle));

    FOverlapResult* ClosestResult = nullptr;
    float MinDistanceSquared = FLT_MAX; // 记录最小距离的平方（避免开根号）

    // 遍历所有 Overlap 结果
    for (const FOverlapResult& Result : Overlaps)
    {
        // 获取目标 Actor
        AActor* TargetActor = Result.GetActor();
        if (!IsValid(TargetActor) || TargetActor == X)
        {
            continue; // 跳过无效 Actor 或自身
        }

        // 计算目标位置到 X 的向量
        const FVector TargetLocation = TargetActor->GetActorLocation();
        const FVector DirToTarget = TargetLocation - XLocation;
        if (DirToTarget.IsNearlyZero(1e-3f))
        {
            continue; // 忽略位置完全重合的情况
        }

        // 标准化方向向量并计算点积
        const FVector NormalizedDir = DirToTarget.GetSafeNormal();
        const float DotProduct = FVector::DotProduct(XForward, NormalizedDir);

        // 检查是否在角度阈值内
        if (DotProduct >= CosTheta)
        {
            // 计算距离平方（优化性能）
            const float DistanceSquared = DirToTarget.SizeSquared();

            // 更新最近结果
            if (DistanceSquared < MinDistanceSquared)
            {
                MinDistanceSquared = DistanceSquared;
                ClosestResult = const_cast<FOverlapResult*>(&Result); // 强制去 const（需谨慎）
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
