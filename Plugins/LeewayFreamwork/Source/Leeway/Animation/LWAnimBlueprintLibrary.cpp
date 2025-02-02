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

// ���� Impact �� B ����� ACharacter A �ķ�λ
void CalculateHitDirection(const ACharacter* Target, const ACharacter* Source, const FVector& Point, ELWHitDirectionF& DirF, ELWHitDirectionH& DirH, ELWHitDirectionV& DirV)
{
    if (!Target) return; // Ĭ��ֵ

    // ��ȡ A �Ľ��������
    UCapsuleComponent* Capsule = Target->GetCapsuleComponent();
    if (!Capsule) return; // Ĭ��ֵ

    // ��ȡ A ��λ�úͽ�����߶�
    FVector LocationA = Target->GetActorLocation();
    float CapsuleHalfHeight = Capsule->GetScaledCapsuleHalfHeight();

    // ���� Impact �� B ����� A �ľֲ�λ��
    FVector LocalS = Source->GetActorLocation() - LocationA;
    FVector LocalB = Point - LocationA;

    // �ж� Upper/Center/Lower
    bool IsUpper = LocalB.Z > CapsuleHalfHeight * 0.5f;
    bool IsLower = LocalB.Z < -CapsuleHalfHeight * 0.2f;

    // ��ȡ A ��ǰ�����������
    FVector ForwardA = Target->GetActorForwardVector();
    FVector RightA = Target->GetActorRightVector();

    // ���� B ����� A �ķ�������
    FVector DirectionB = LocalS;
    DirectionB.Z = 0; // ���Ը߶ȣ�������ˮƽ����
    DirectionB.Normalize();

    // ���������ж�ǰ��
    float DotProductForward = FVector::DotProduct(ForwardA, DirectionB);

    // ���������ж����ң�
    float DotProductRight = FVector::DotProduct(RightA, DirectionB);

    // �ж�ǰ������
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
    // ��ȡ Actor B ��ǰ������
    FVector ActorBDir = TargetActor->GetActorForwardVector();
    ActorBDir.Z = 0.f; // ȡˮƽ����
    ActorBDir.Normalize();

    // ���� Actor A ����� Actor B ������
    FVector RelativePos = SourceActor->GetActorLocation() - TargetActor->GetActorLocation();
    FVector RelativeV = HitPoint - TargetActor->GetActorLocation();
    FVector HorizontalRelativePos = RelativePos;
    HorizontalRelativePos.Z = 0.f;
    HorizontalRelativePos.Normalize();

    // ǰ��ά��
    float FrontBack = FVector::DotProduct(ActorBDir, HorizontalRelativePos);

    // ����ά��
    FVector CrossProduct = FVector::CrossProduct(ActorBDir, HorizontalRelativePos);
    float LeftRight = CrossProduct.Z;

    // ����ά��
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
