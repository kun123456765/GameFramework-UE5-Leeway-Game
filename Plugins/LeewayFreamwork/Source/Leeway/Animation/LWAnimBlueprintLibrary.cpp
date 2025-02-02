//--------------------
// kun 2025.01.27
//--------------------

#include "LWAnimBlueprintLibrary.h"
#include "Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Leeway/Animation/AnimMetaData/LWAnimMetaData_HitReaction.h"
#include "Leeway/GameplayCommon/ActorTargeting/ActorTargetingTypes.h"

FName ULWAnimBlueprintLibrary::ChooseFittestMontageSectionForHitReaction(const UAnimMontage* MontageToPlay, const FAnimMetaData_HitReaction& InMetaData)
{
    //UE_LOGD(TEXT("Calc Section: %d, %d, %d, %d, Tensor=(%s)"), InMetaData.DirF, InMetaData.DirH, InMetaData.DirV, InMetaData.Intensity, *InMetaData.DirTensor.ToString());
    if (MontageToPlay)
    {
        int BestSectionIndex = 0;
        int MinDirectionDistance = INT_MAX;

        float MinDirDisntance_Tensor = FLT_MAX;
        const ULWAnimMetaData_HitReaction* BestMetaData = nullptr;
        const TArray<FCompositeSection>& Sections = MontageToPlay->CompositeSections;
        for (int i = 0, ic = Sections.Num(); i < ic; ++i)
        {
            auto& Section = Sections[i];
            auto& MetaDataArray = Section.GetMetaData();
            for (const auto* MetaData : MetaDataArray)
            {
                if (auto* LWMetaData = Cast<ULWAnimMetaData_HitReaction>(MetaData))
                {
                    int DF = FMath::Abs((uint8)LWMetaData->Data.DirF - (uint8)InMetaData.DirF);
                    int DH = FMath::Abs((uint8)LWMetaData->Data.DirH - (uint8)InMetaData.DirH);
                    int DV = FMath::Abs((uint8)LWMetaData->Data.DirV - (uint8)InMetaData.DirV);
                    int DI = (uint8)LWMetaData->Data.Intensity - (uint8)InMetaData.Intensity;
                    int Distance = DF * 40 + DH * 20 + DV * 10 + DI;
                    if (Distance < MinDirectionDistance)
                    {
                        MinDirectionDistance = Distance;
                        BestSectionIndex = i;
                        BestMetaData = LWMetaData;
                    }

                    float TensorDistance = FVector::Distance(InMetaData.DirTensor, LWMetaData->Data.DirTensor);
                    if (TensorDistance < MinDirDisntance_Tensor)
                    {
                        MinDirDisntance_Tensor = TensorDistance;
                        BestSectionIndex = i;
                        BestMetaData = LWMetaData;
                    }
                    //UE_LOGD(TEXT("Montage: %d, %d, %d, %d, WeightDis = %d, TenderDis = %f, (%s)"), LWMetaData->Data.DirF, LWMetaData->Data.DirH, LWMetaData->Data.DirV, LWMetaData->Data.Intensity, Distance, TensorDistance, *MontageToPlay->GetSectionName(i).ToString());
                }
            }
        }

        if (BestMetaData)
        {
            //UE_LOGD(TEXT("Best Section: %d, %d, %d, %d, (%s)"), BestMetaData->Data.DirF, BestMetaData->Data.DirH, BestMetaData->Data.DirV, BestMetaData->Data.Intensity, *MontageToPlay->GetSectionName(BestSectionIndex).ToString());
        }

        return MontageToPlay->GetSectionName(BestSectionIndex);
    }

    return FName();
}

// 计算 Impact 点 B 相对于 ACharacter A 的方位
void CalculateHitDirection(const ACharacter* Target, const ACharacter* Source, const FVector& Point, ELWHitDirectionF& DirF, ELWHitDirectionH& DirH, ELWHitDirectionV& DirV)
{
    if (!Target) return; // 默认值

    // 获取 A 的胶囊体组件
    UCapsuleComponent* Capsule = Target->GetCapsuleComponent();
    if (!Capsule) return; // 默认值

    // 获取 A 的位置和胶囊体高度
    FVector LocationA = Target->GetActorLocation();
    float CapsuleHalfHeight = Capsule->GetScaledCapsuleHalfHeight();

    // 计算 Impact 点 B 相对于 A 的局部位置
    FVector LocalS = Source->GetActorLocation() - LocationA;
    FVector LocalB = Point - LocationA;

    // 判断 Upper/Center/Lower
    bool IsUpper = LocalB.Z > CapsuleHalfHeight * 0.5f;
    bool IsLower = LocalB.Z < -CapsuleHalfHeight * 0.2f;

    // 获取 A 的前向和右向向量
    FVector ForwardA = Target->GetActorForwardVector();
    FVector RightA = Target->GetActorRightVector();

    // 计算 B 相对于 A 的方向向量
    FVector DirectionB = LocalS;
    DirectionB.Z = 0; // 忽略高度，仅考虑水平方向
    DirectionB.Normalize();

    // 计算点积（判断前后）
    float DotProductForward = FVector::DotProduct(ForwardA, DirectionB);

    // 计算点积（判断左右）
    float DotProductRight = FVector::DotProduct(RightA, DirectionB);

    // 判断前后左右
    bool IsFront = DotProductForward >= 0.f;
    //bool IsBack = DotProductForward < 0.f;
    bool IsMiddle = FMath::Abs(DotProductForward) > 0.5f;
    bool IsRight = DotProductRight > 0.0f;
    bool IsLeft = DotProductRight < 0.0f;

    DirF = IsFront ? ELWHitDirectionF::Front : ELWHitDirectionF::Back;
    DirH = IsMiddle ? ELWHitDirectionH::Mid : IsRight ? ELWHitDirectionH::Right : ELWHitDirectionH::Left;
    DirV = IsUpper ? ELWHitDirectionV::Upper : IsLower ? ELWHitDirectionV::Lower : ELWHitDirectionV::Center;
}

FVector CalculateRelativePositionVector(const ACharacter* TargetActor, const ACharacter* SourceActor, const FVector& HitPoint)
{
    // 获取 Actor B 的前方向量
    FVector ActorBDir = TargetActor->GetActorForwardVector();
    ActorBDir.Z = 0.f; // 取水平向量
    ActorBDir.Normalize();

    // 计算 Actor A 相对于 Actor B 的向量
    FVector RelativePos = SourceActor->GetActorLocation() - TargetActor->GetActorLocation();
    FVector RelativeV = HitPoint - TargetActor->GetActorLocation();
    FVector HorizontalRelativePos = RelativePos;
    HorizontalRelativePos.Z = 0.f;
    HorizontalRelativePos.Normalize();

    // 前后维度
    float FrontBack = FVector::DotProduct(ActorBDir, HorizontalRelativePos);

    // 左右维度
    FVector CrossProduct = FVector::CrossProduct(ActorBDir, HorizontalRelativePos);
    float LeftRight = CrossProduct.Z;

    // 上下维度
    float CapsuleHalfHeight = TargetActor->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
    float UpDown = RelativeV.Z / CapsuleHalfHeight;

    return FVector(FrontBack, LeftRight, UpDown);
}

FName ULWAnimBlueprintLibrary::ChooseFittestMontageSectionForHitReactionWithActor(const UAnimMontage* MontageToPlay, const ACharacter* TargetActor, const ACharacter* SourceActor, const FTargetingResult_Overlap& OverlapResult)
{
    FAnimMetaData_HitReaction Query;
    Query.DirF = ELWHitDirectionF::Front;
    Query.DirH = ELWHitDirectionH::Mid;
    Query.DirV = ELWHitDirectionV::Center;
    Query.Intensity = ELWHitIntensity::Shudder;
    if (OverlapResult.PhysicsAsset.BoneName != NAME_None)
    {
        CalculateHitDirection(TargetActor, SourceActor, OverlapResult.PhysicsAsset.ClosestWorldPosition, Query.DirF, Query.DirH, Query.DirV);
        Query.DirTensor = CalculateRelativePositionVector(TargetActor, SourceActor, OverlapResult.PhysicsAsset.ClosestWorldPosition);
    }

    return ChooseFittestMontageSectionForHitReaction(MontageToPlay, Query);
}
