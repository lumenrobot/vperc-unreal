// Fill out your copyright notice in the Description page of Project Settings.

using System.IO;
using UnrealBuildTool;

public class vperc : ModuleRules
{
    
    private string ModulePath { 
        get {
            return Path.GetDirectoryName(RulesCompiler.GetModuleFilename(this.GetType().Name));
        }
    }

    private string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }

    private string BoostPath { 
        get {
            return Path.GetFullPath("C:/local/boost_1_57_0");
        }
    }

	public vperc(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");
		// if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
		// {
		//		if (UEBuildConfiguration.bCompileSteamOSS == true)
		//		{
		//			DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
		//		}
		// }

        LoadBoost(Target);
        LoadSimpleAmqpClient(Target);
	}

    bool LoadBoost(TargetInfo Target)
    {
        Definitions.Add("BOOST_ALL_NO_LIB");
        // BTW, for Unreal4+Boost+SimpleAmqpClient to work,
        // SimpleAmqpClient must be Release (not Debug) and *requires* the mt-only version of boost libs (system+chrono)
        // otherwise std::string will be corrupted when passing to SimpleAmqpClient DLL
        PublicAdditionalLibraries.Add(Path.Combine(BoostPath, "lib64-msvc-12.0/boost_system-vc120-mt-1_57.lib"));
        // chrono required by SimpleAmqpClient, but we don't need to link to the .lib because we don't use it,
        // but SimpleAmqpClient will dynlink to the chrono .dll on its own
        //PublicAdditionalLibraries.Add(Path.Combine(BoostPath, "lib64-msvc-12.0/boost_chrono-vc120-mt-1_57.lib"));
        PublicIncludePaths.Add(BoostPath);
        return true;
    }

    bool LoadSimpleAmqpClient(TargetInfo Target)
    {
        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "lib_win64/rabbitmq.4.lib"));
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "librabbitmq"));

        PublicAdditionalLibraries.Add(Path.Combine(ThirdPartyPath, "lib_win64/SimpleAmqpClient.2.lib"));
        PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "SimpleAmqpClient"));

        return true;
    }

}
