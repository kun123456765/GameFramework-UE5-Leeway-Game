//--------------------
// kun 2024.12.22
//--------------------

using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class Leeway : ModuleRules
{
    public Leeway(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        // ���Ԥ����ͷ�ļ�
        PrivatePCHHeaderFile = "PreEngine/Runtime/Core/Private/LeewayPCH.h";

        PublicDependencyModuleNames.AddRange(new string[]
        {
            //defaults
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "AIModule",
            "Niagara",

            //add by kun 2025.01.17 for locomotion
            "AnimGraphRuntime",
            //add by kun 2025.01.17 for locomotion
            "GameplayTags",
            //add by kun 2025.01.21 for GAS
            "GameplayAbilities",
            //add by kun 2025.01.22 for GAS
			"GameplayTasks",
            //add by kun 2025.01.30 for the PushMode of Replication;
			"NetCore",
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            //add by kun 2025.01.17 for locomotion
            "AnimGraph",
            //add by kun 2025.01.17 for locomotion
            "AnimationLocomotionLibraryRuntime",
        });

        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(new string[]
            {
                //add by kun 2025.01.17 for locomotion
                "AnimationBlueprintLibrary",
            });
        }
    }
}
