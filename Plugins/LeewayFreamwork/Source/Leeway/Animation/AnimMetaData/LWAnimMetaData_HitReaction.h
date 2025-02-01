//--------------------
// kun 2025.01.31
//--------------------

#pragma once

#include "BaseAnimMetaData.h"
#include "LWAnimMetaData_HitReaction.generated.h"

UENUM(BlueprintType)
enum class ELWHitDirectionF : uint8
{
	Front,
	Back,
};

UENUM(BlueprintType)
enum class ELWHitDirectionH : uint8
{
	Left,
	Mid,
	Right,
};

UENUM(BlueprintType)
enum class ELWHitDirectionV : uint8
{
	Upper,
	Center,
	Lower,
};

UENUM(BlueprintType)
enum class ELWHitIntensity : uint8
{
	// �������Ϊ����3C���㶯��ʵ��;
	Jolt, // ��Ϊ ���𶯣�������ҡ�Ρ���ͨ����ʾͻȻ�ġ���΢���𶯻�ҡ�Σ����ʺ�������ɫ�ܵ���΢����ʱ�����˲�䷴Ӧ��
	Flinch, // ָ ��������η����������ɫ�ܵ�����Ĵ��ʱ�����ܻ᱾�ܵ����������Ķ�����

	// ���⼶��ʼȫ�������Ϊ��ȫ��Montage����;
	// ԭ���ܻ�����;
	Shudder, // �� ��ս���������� ����˼�����ֳ��ܻ���������ݵ���΢���������Ƚ�С��
	Sway, // ��Ϊ ��ҡ�ڣ��ζ���������� ��Stagger������Sway�� ���ܶ��������һЩ����Ҳ�����ֽ�ɫ���ܻ�������İڶ���

	// ��λ���ܻ�, ����Rootmotion���������ƥ��;
	Stagger, // ��ʾ �����ǣ�ҡ�Σ����ġ�����ɫ�ܵ�һ���̶ȹ���������ʧȥƽ���ҡ�Ρ���·���ȵ�״̬��
	KnockBack, // �����ˡ���ָ��ɫ�ܵ�ǿ�󹥻�������ƵĶ������ܻ����Ƚϴ�

	// ���أ�����Stance״̬�л���(StanceStance->GroundStance)
	KnockOut, // ����������衱���������ص��ܻ��������ɫֱ��ʧȥ�ж��������ء�

	// ���ɣ�����״̬�л�(StandStance->FlyStance)���˶�ģʽҲҪ��(Moving->Flying)
	KnockAway, // �����ɡ�������ԭ�ء�
};


USTRUCT(BlueprintType)
struct FAnimMetaData_HitReaction
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	ELWHitDirectionF DirF;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	ELWHitDirectionH DirH;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	ELWHitDirectionV DirV;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	FVector DirTensor = FVector(1, 0, 0);

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	ELWHitIntensity Intensity;
};

UCLASS(MinimalAPI, Blueprintable)
class ULWAnimMetaData_HitReaction : public UBaseAnimMetaData
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	FAnimMetaData_HitReaction Data;
};
