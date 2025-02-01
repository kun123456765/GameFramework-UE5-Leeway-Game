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
	// 不打断行为，用3C叠层动作实现;
	Jolt, // 意为 “震动；颠簸；摇晃”，通常表示突然的、轻微的震动或摇晃，很适合描述角色受到轻微攻击时身体的瞬间反应。
	Flinch, // 指 “退缩；畏缩”，当角色受到较轻的打击时，可能会本能地做出退缩的动作。

	// 从这级开始全部打断行为，全是Montage动作;
	// 原地受击动作;
	Shudder, // 有 “战栗；颤抖” 的意思，体现出受击后身体短暂的轻微颤抖，幅度较小。
	Sway, // 意为 “摇摆；晃动”，相较于 “Stagger”，“Sway” 可能动作更柔和一些，但也能体现角色在受击后身体的摆动。

	// 带位移受击, 根据Rootmotion最大距离进行匹配;
	Stagger, // 表示 “蹒跚；摇晃；踉跄”，角色受到一定程度攻击后，身体失去平衡而摇晃、走路不稳的状态。
	KnockBack, // “击退”，指角色受到强大攻击后被向后推的动作，受击幅度较大。

	// 倒地，发生Stance状态切换。(StanceStance->GroundStance)
	KnockOut, // “击倒；打昏”，是最严重的受击情况，角色直接失去行动能力倒地。

	// 击飞，发生状态切换(StandStance->FlyStance)，运动模式也要换(Moving->Flying)
	KnockAway, // “击飞”，飞离原地。
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
